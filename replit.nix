{ pkgs, legacyPolygott }: {
	deps = [
        pkgs.bashInteractive
        pkgs.nodePackages.bash-language-server
        pkgs.man
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
        pkgs.libGL
        pkgs.libGLU
        pkgs.freeglut
	] ++ legacyPolygott;
}