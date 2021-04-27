const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const obj = b.addObject("color", "color.zig");

    const exe = b.addExecutable("chue", null);
    exe.addCSourceFile("main.c", &[_][]const u8{ "-std=c99", "-D_XOPEN_SOURCE" });
    exe.addCSourceFile("parse.c", &[_][]const u8{"-std=c99"});
    exe.addCSourceFile("display.c", &[_][]const u8{"-std=c99"});
    exe.addObject(obj);

    exe.linkSystemLibrary("c");
    exe.install();
}
