const std = @import("std");
const math = std.math;
const mem = std.mem;

// XXX: stahp reformatting my space alignment !!!
pub const RGB = extern struct { r: u8, g: u8, b: u8 }; // XXX: et tu, zig?
pub const HSV = extern struct { h: f64, s: f64, v: f64 };
pub const HSL = extern struct { h: f64, s: f64, l: f64 };

fn _hue_to_rgb(p: f64, q: f64, _t: f64) f64 {
    // XXX: let me assign to my params!
    var t = _t;

    if (t < 0.0) t += 1.0;
    if (t > 1.0) t -= 1.0;

    if (t < 1.0 / 6.0)
        return p + (q - p) * 6.0 * t;
    if (t < 1.0 / 2.0)
        return q;
    if (t < 2.0 / 3.0)
        return p + (q - p) * (2.0 / 3.0 - t) * 6.0;

    return p;
}

pub export fn rgb_from_hsl(_h: f64, _s: f64, _l: f64) RGB {
    const h = _h / 360.0;
    const s = _s / 100.0;
    const l = _l / 100.0;

    var r: f64 = 0.0;
    var g: f64 = 0.0;
    var b: f64 = 0.0;

    if (s == 0.0) { // achromatic
        r = l;
        g = l;
        b = l;
    } else {
        var q = if (l < 0.5) l * (1.0 + s) else l + s - l * s;
        var p = 2.0 * l - q;

        r = _hue_to_rgb(p, q, h + (1.0 / 3.0));
        g = _hue_to_rgb(p, q, h);
        b = _hue_to_rgb(p, q, h - (1.0 / 3.0));
    }

    return .{
        .r = @floatToInt(u8, math.round(r * 255.0)),
        .g = @floatToInt(u8, math.round(g * 255.0)),
        .b = @floatToInt(u8, math.round(b * 255.0)),
    };
}

pub export fn rgb_from_hsv(h: f64, _s: f64, _v: f64) RGB {
    const s = _s / 100;
    const v = _v / 100;

    if (s <= 0.0) {
        return .{
            .r = @floatToInt(u8, v),
            .g = @floatToInt(u8, v),
            .b = @floatToInt(u8, v),
        };
    }

    const hh = (if (h >= 360.0) 0.0 else h) / 60.0;
    const i = @floatToInt(usize, hh);
    const ff = hh - @intToFloat(f64, i);
    const p = v * (1.0 - s);
    const q = v * (1.0 - (s * ff));
    const t = v * (1.0 - (s * (1.0 - ff)));

    var tr: f64 = 0.0;
    var tg: f64 = 0.0;
    var tb: f64 = 0.0;

    // XXX: switch cases are lovely
    switch (@floatToInt(usize, math.round(h / 60.0))) {
        0 => {
            tr = v;
            tg = t;
            tb = p;
        },
        1 => {
            tr = q;
            tg = v;
            tb = p;
        },
        2 => {
            tr = p;
            tg = v;
            tb = t;
        },
        3 => {
            tr = p;
            tg = q;
            tb = v;
        },
        else => {
            tr = v;
            tg = p;
            tb = q;
        },
    }

    return .{
        .r = @floatToInt(u8, math.round(tr * 255.0)),
        .g = @floatToInt(u8, math.round(tg * 255.0)),
        .b = @floatToInt(u8, math.round(tb * 255.0)),
    };
}

pub export fn hsv_from_rgb(rgb: RGB) HSV {
    // XXX: guh type inference is a thing
    var hue: f64 = 0.0;
    var saturation: f64 = 0.0;
    var value: f64 = 0.0;

    const tr = @intToFloat(f64, rgb.r) / 255.0;
    const tg = @intToFloat(f64, rgb.g) / 255.0;
    const tb = @intToFloat(f64, rgb.b) / 255.0;

    // XXX: why is max in mem
    const Xmax = mem.max(f64, &[_]f64{ tr, tg, tb });
    const Xmin = mem.min(f64, &[_]f64{ tr, tg, tb });
    const C = Xmax - Xmin;

    value = Xmax;
    saturation = if (Xmax == 0) 0 else C / Xmax;

    if (C == 0.0) {
        hue = 0;
    } else if (Xmax == tr) {
        hue = 60.0 * (((tg - tb) / C) + 0.0);
    } else if (Xmax == tg) {
        hue = 60.0 * (((tb - tr) / C) + 2.0);
    } else if (Xmax == tb) {
        hue = 60.0 * (((tr - tg) / C) + 4.0);
    }

    if (hue < 0.0) hue += 360.0;

    return .{
        .h = hue,
        .s = saturation * 100,
        .v = value * 100,
    };
}

pub export fn hsl_from_rgb(rgb: RGB) HSL {
    var hsl: HSL = HSL{ .h = undefined, .s = undefined, .l = undefined };

    const tr = @intToFloat(f64, rgb.r) / 255.0;
    const tg = @intToFloat(f64, rgb.g) / 255.0;
    const tb = @intToFloat(f64, rgb.b) / 255.0;

    // XXX: Why do I have to pass the type along everywhere
    const Xmax = mem.max(f64, &[_]f64{ tr, tg, tb });
    const Xmin = mem.min(f64, &[_]f64{ tr, tg, tb });
    hsl.l = (Xmax + Xmin) / 2;

    if (Xmax == Xmin) { // achromatic
        hsl.h = 0.0;
        hsl.s = 0.0;
    } else {
        const d = Xmax - Xmin;
        hsl.s = if (hsl.l > 0.5)
            d / (2.0 - Xmax - Xmin)
        else
            d / (Xmax + Xmin);

        if (Xmax == tr) {
            const o: f64 = if (tg < tb) 6.0 else 0.0;
            hsl.h = (tg - tb) / d + o;
        } else if (Xmax == tg) {
            hsl.h = (tb - tr) / d + 2.0;
        } else if (Xmax == tb) {
            hsl.h = (tr - tg) / d + 4.0;
        } else {
            @panic("The sky is falling~");
        }

        hsl.h /= 6.0;
    }

    hsl.h *= 360.0;
    hsl.s *= 100.0;
    hsl.l *= 100.0;

    return hsl;
}
