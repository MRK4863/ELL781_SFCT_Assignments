    struct graph_adt* g = load_graph(file_name);
    printf("\n%d\n", g->adj_matrix[6][3]);
    print_graph(g);
    struct graph_adt* MST;
    print_graph(g);
    MST = prim(g, 1);
    printf("\nRECIEVED MST");
    print_graph(MST);
