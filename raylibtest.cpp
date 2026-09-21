#include <raylib.h>
#include <graph.hpp>
#include <vector>

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
    Graph<int>* G = new Graph<int>(true,true);
    Node<int>* nodeA = G->add_node(0,"A",100.0f,100.0f);
    Node<int>* nodeB = G->add_node(1,"B",100.0f,90.0f);
    Node<int>* nodeC = G->add_node(2,"C",100.0f,70.0f);
    Node<int>* nodeD = G->add_node(3,"D",100.0f,50.0f);
    Node<int>* nodeE = G->add_node(4,"E",100.0f,30.0f);
    Node<int>* nodeF = G->add_node(5,"F",100.0f,10.0f);
    Node<int>* nodeG = G->add_node(6,"G",140.0f,100.0f);
    Node<int>* nodeH = G->add_node(7,"H",200.0f,80.0f);
    G->add_edge(nodeA, nodeB, 0);
    G->add_edge(nodeB, nodeC, 0);
    G->add_edge(nodeC, nodeD, 0);
    G->add_edge(nodeD, nodeE, 0);
    G->add_edge(nodeE, nodeF, 0);
    G->add_edge(nodeA, nodeG, 0);
    G->DFS(nodeA,true);
    G->print_topological_order();
    WindowArgs* defaultArgs = new WindowArgs(640,480,2,"test");
    InitWindow( defaultArgs->screenWidth,
                defaultArgs->screenHeight,
                defaultArgs->title);
    SetTargetFPS(defaultArgs->fps);
    int color_iter = 0;
    std::vector<Color> colors = {RED,BLUE,GREEN,YELLOW};
    while (!WindowShouldClose()){
        bool next_step = false;
        color_iter = color_iter%colors.size();
        BeginDrawing();
            ClearBackground(WHITE);
            for (size_t i = 0; i < G->get_nodes_size() ; i++) {
                auto aux = G->get_node_by_value(i);
                if (aux != nullptr){
                    DrawCircle( aux->get_x(),
                                aux->get_y(),
                                5.0f,
                                colors.at(color_iter));
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
        color_iter++;
    }
    CloseWindow();
    return 0;
}
