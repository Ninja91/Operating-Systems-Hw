int app() {
    kprintf("\nIn app process");
    char * string  = (char *) vgetmem(sizeof("Nitin"));
    string = "Nitin";
    vfreemem(string, sizeof("Nitin"));    
    /* while(1); */
    return 0;
}
