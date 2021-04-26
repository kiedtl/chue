// This file is borken. Just use make.
//
const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const exe = b.addCExecutable("chue");
    exe.addCompileFlags([][]const u8{ "-std=c99", "-I.", "-Iccommon/include" });

    const source_files = [][]const u8{
        "main.c",
        "display.c",
        "parse.c",
    };
    const zig_source_files = [][]const u8{
        "color.zig",
    };

    for (source_files) |source| {
        exe.addSourceFile(source);
    }

    for (zig_source_files) |source| {
        const object = b.addObject(source, source);
        exe.addObject(object);
    }

    exe.setOutputPath("./chue");
    b.default_step.dependOn(&exe.step);
}
