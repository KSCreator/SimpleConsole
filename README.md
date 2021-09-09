# SimpleConsole
A simple interactive terminal made with qt.

<h2> To build it </h2>
<p>run the following command </p>
cmake -B build -S . <br>
cd build <br>
make
<br>
<br>
<h2> To run it </h2>
  <p>
    Execute any_program with no argument
    <br>
    ./Console -p any_program
  </p>
  <p>
    Execute any_program with 3 arguments
    <br>
    ./Console -p any_program arg1 arg2 arg3
  </p>
  <p>
    Execute any_program with 3 arguments with setting qt style to "fusion"
    <br>
    ./Console -style fusion -p any_program arg1 arg2 arg3
</p>
<h2> Usage </h2>
  Console [qt_options] -p program_name [arguments]
  <p>qt_options (such as -style option) must be passed before -p, the rest arguments after -p will be used for program's arguments.</p>
