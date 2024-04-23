int interpolationSearchDescending(Hero* hero_list, int l, int r, const string& nama) {
    while (l <= r && hero_list[r].nama >= nama && hero_list[l].nama <= nama) {
        if (hero_list[r].nama == hero_list[l].nama) {
            if (hero_list[l].nama == nama) return l;
            return -1;
        }

        // Perbaikan pada bagian perhitungan fraction
        double fraction = static_cast<double>(nama[0] - hero_list[l].nama[0]) / (hero_list[l].nama[0] - hero_list[r].nama[0]);
        int pos = l + static_cast<int>((r - l) * fraction);

        // Perbaikan untuk memastikan posisi tidak melebihi r
        if (pos > r) pos = r;

        if (hero_list[pos].nama == nama) return pos;
        if (hero_list[pos].nama < nama) r = pos - 1;
        else l = pos + 1;
    }
    return -1;
}