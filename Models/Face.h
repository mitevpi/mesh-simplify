class Face {
public:
    Face(int x, int y, int z);
    int x;
    int y;
    int z;

    static Face parseFace(const std::string& x, const std::string& y, const std::string& z){
        return Face(stoi(x), stoi(y), stoi(z));
    }
};

Face::Face(int x, int y, int z){
    Face::x = x;
    Face::y = y;
    Face::z = z;
}

