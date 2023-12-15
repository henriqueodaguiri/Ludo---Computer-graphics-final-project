echo hello
nix-shell -p libGL libGLU freeglut --run '
    # Command 1
    echo "Running GCC compile command"
    bash -c "time gcc ludo.c -lglut -lGL -lGLU -lm -o ludo" > >(tee -a output.log) 2>&1

    # Command 2
    echo "Starting compiled program"
    bash -c "./ludo"

    # Example Command 3
    #echo "Running Command 3"
    #bash -c "echo hmm3"
'
#gcc test.c -lglut -lGL -o testprog