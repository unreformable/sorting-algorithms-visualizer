#include "Application.hh"



int main(int, char**)
{
    Application app(WindowProps(600, 600, "Sorting Algorithms Visualizer"));
    app.run();

    return EXIT_SUCCESS;
}