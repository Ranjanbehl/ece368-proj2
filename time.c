    clock_t t; 
    t = clock(); 
    tree = HuffmanTree(chararray,freqarray,cnt);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("Building the tree took %f \n", time_taken);
    height = Max_Height(tree);

    clock_t t2; 
    t2 = clock(); 
    hufftable = createHuffTable(tree);
    t2 = clock() - t2; 
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds 
    printf("Building the codebook took %f \n", time_taken2);


    clock_t t3; 
    t3 = clock(); 
    encode(argv[1],hufftable,tree,ascii_array,cnt,height); // works but overall huff is super slow
    t3 = clock() - t3; 
    double time_taken3 = ((double)t3)/CLOCKS_PER_SEC; // in seconds 
    printf("Encoding the file took %f seconds \n", time_taken3);