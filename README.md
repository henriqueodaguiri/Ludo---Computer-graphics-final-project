replit demo/template for freeGLUT.

can fork this template and build C demos using GCC or C++ using G++

script.sh sets up the nix shell & packages, runs GCC and compiles shading.c on each run








2nd May 23rd 2023 update:
============================================================
modified script.sh and the replit config, this should now start as a "bash" replit , and run start.sh .

start.sh fires off nix-shell -p with the 3 needed libraries, and then tells bash to execute our gcc build command (inside the new nix shell) and then starts the program

todo:
- fix start script to check if output file already exists
- try out other freeglut demos, make sure more than this one works









this repl is broken in NIX, latest update May 23rd 2023:
============================================================
i was able to get a bit more progress on this, i installed nix on a local machine because i was getting some odd errors out of replit.

These commands worked for me (on physical machine but not on replit)
#############

$ nix-shell -p libGL libGLU freeglut
these 4 paths will be fetched (0.31 MiB download, 2.64 MiB unpacked):
/nix/store/ghj6b2778j9rg7392rzg34k8h1pq3q8j-glu-9.0.2
/nix/store/aplyv385h2d4yibzij4kg332iwvnmz1s-glu-9.0.2-dev
/nix/store/bk5lpxbpw3545dcdcbv1n5nf33i84k6s-libGL-1.6.0-dev
/nix/store/syfid5mrc3w354m9dpsknhkz80c7a7pm-libglvnd-1.6.0-dev
copying path '/nix/store/ghj6b2778j9rg7392rzg34k8h1pq3q8j-glu-9.0.2' from 'https://cache.nixos.org'...
copying path '/nix/store/syfid5mrc3w354m9dpsknhkz80c7a7pm-libglvnd-1.6.0-dev' from 'https://cache.nixos.org'...
copying path '/nix/store/bk5lpxbpw3545dcdcbv1n5nf33i84k6s-libGL-1.6.0-dev' from 'https://cache.nixos.org'...
copying path '/nix/store/aplyv385h2d4yibzij4kg332iwvnmz1s-glu-9.0.2-dev' from 'https://cache.nixos.org'...

[nix-shell:~]$ gcc test.c -lglut -lGL -o testprog

#########################
^^ this is using the same c code file from this repl, i was able to build it but on replit.com it gives me an error saying something about the video output device

stack exchange posts suggested running glxinfo to confirm what opengl support was visible to the shell

glxinfo doesnt work on replit, but works on my local machine with nix - i opened a replit bug, i think there is some missing component , configuration or possibly a bug with accessing the output device , i am not certain but i will check in on this and work some more
https://ask.replit.com/t/glxinfo-returns-error-libpthread-so-0-undefined-symbol-libc-siglongjmp-version-glibc-private/33614


