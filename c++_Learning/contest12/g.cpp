bool comp(string x, string y) {
    if (x.size() != y.size()) {
        return x.size() < y.size();
    }
    int xx = 0, yy = 0;
    for (auto it : x) {
        xx += it == '1';
    }
    for (auto it : y) {
        yy += it == '1';
    }
    if (xx != yy) {
        return xx < yy;
    }
    return x < y;
}
