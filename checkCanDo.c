int checkCanDo(int x, int y, char* map){
    if(map[y*x+y+1]==0) return 1;
    else 0;
}