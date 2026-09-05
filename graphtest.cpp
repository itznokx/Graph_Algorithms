#include "libcpp/graph.hpp"
#include "visualizer-lib/build/external/raylib-master/src/raylib.h"
#include <raylib.h>

struct WindowArgs {
    int screenWidth;
    int screenHeight;
    int fps;
    const char* title;
    WindowArgs (int sw,int sh,int fp, const char* _title) :
                screenWidth(sw), screenHeight(sh), fps(fp), title(_title)

                {};
};

int main (void) {
    WindowArgs* defaultArgs = new WindowArgs(640,480,30,"test");
    Graph<int>* G = new Graph<int>(true,true);
    Node<int>* nodeA = G->add_node(0,"A",100.0f,100.0f);
    Node<int>* nodeB = G->add_node(1,"B",100.0f,130.0f);
    Node<int>* nodeC = G->add_node(2,"C",100.0f,70.0f);
    Node<int>* nodeD = G->add_node(3,"D",200.0f,80.0f);
    G->add_edge(nodeA, nodeB, 0);
    G->add_edge(nodeA, nodeC, 0);
    G->add_edge(nodeA, nodeD, 0);
    G->add_edge(nodeB, nodeD, 0);
    size_t nodes_size = G->get_nodes_size();
    InitWindow( defaultArgs->screenWidth,
                defaultArgs->screenHeight,
                defaultArgs->title);
    SetTargetFPS(defaultArgs->fps);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);
            for (size_t i = 0; i < G->get_nodes_size() ; i++) {
                auto aux = G->get_node_by_value(i);
                if (aux != nullptr){
                    DrawCircle( aux->get_x(),
                                aux->get_y(),
                                5.0f,
                                RED);
                    for (const auto& edge : aux->get_full_neighbour()) {
                        DrawLine(
                            aux->get_x(),aux->get_y(),
                            edge->target->get_x(), edge->target->get_y(),
                            BLACK
                        );
                    }
                }
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
