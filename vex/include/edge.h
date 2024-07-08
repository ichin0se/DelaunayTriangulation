struct EDGE{
    int first, second;

    int first(){
        return min(first, second);
    }

    int second(){
        return max(first, second);
    }
}
