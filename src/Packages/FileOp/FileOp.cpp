/* 
 * File:   FileOp.cpp
 * Author: darlan
 * 
 * Created on 21 de Janeiro de 2016, 12:42
 */

#include <FileOp.h>
#include <yaml-cpp/emitter.h>

using namespace YAML;

FileOp::FileOp() {
}

FileOp::FileOp(const FileOp& orig) {
    node = orig.node;
    FileName = orig.FileName;
    isopen = orig.isopen;
    mode = orig.mode;
}

FileOp::FileOp(const string& Filename) {
    SaveFile.open(Filename.c_str(),ios::out|ios::in|ios::app);
    if(!SaveFile.is_open()){
        cerr << "Can't open file: " << Filename << endl;
        isopen = false;
        return;
    }
    FileName = Filename;
    node = LoadFile(FileName);
    SaveFile.close();
    isopen = true;
    mode = ios::out|ios::in|ios::app;
}
FileOp FileOp::operator = (const FileOp& src){
    node = src.node;
    FileName = src.FileName;
    isopen = src.isopen;
    mode = src.mode;
    return *this;
}
FileOp::FileOp(const string& Filename,const ios::openmode& filemode) {
    SaveFile.open(Filename.c_str(),filemode);
    if(!SaveFile.is_open()){
        cerr << "Can't open file: " << Filename << endl;
        isopen = false;
        return;
    }
    FileName = Filename;
    node = LoadFile(FileName);
    SaveFile.close();
    isopen = true;
    mode = filemode;
}

FileOp::~FileOp() {
    if(node.size() != 0){
        if(mode & ios::out){
            SaveFile.open(FileName,ios::out);
            if(!SaveFile.is_open()) return;
            SaveFile << "%YAML:1.2" << endl;
            SaveFile << node << endl;
            if(SaveFile.is_open())
                SaveFile.close();
        }
    }
    node.reset();
}
void FileOp::close(){
    if(node.size() != 0){
        if(mode & ios::out){
            SaveFile.open(FileName,ios::out);
            if(!SaveFile.is_open()) return;
            SaveFile << "%YAML:1.2" << endl;
            SaveFile << node << endl;
            if(SaveFile.is_open())
                SaveFile.close();
        }
    }
    node.reset();
}
void FileOp::Write(const INTERVAL& IN){
    Node InfSupNode,Inode;
    InfSupNode.SetStyle(EmitterStyle::Flow);
    InfSupNode.push_back(IN.ival.inf);
    InfSupNode.push_back(IN.ival.sup);
    Inode.push_back("I");
    Inode.push_back(InfSupNode);
    node.push_back(Inode);
}

void FileOp::Write(const INTERVAL_VECTOR& IN){
    Node VecNode, finalnode;
    VecNode.SetStyle(EmitterStyle::Flow);
    for(int i = 1;i <= Dimension(IN);i++){
        Node InfSupNode;
        InfSupNode.SetStyle(EmitterStyle::Flow);
        InfSupNode.push_back(IN(i).ival.inf);
        InfSupNode.push_back(IN(i).ival.sup);
        VecNode.push_back(InfSupNode);
    }
    finalnode.push_back("IV");
    finalnode.push_back(Dimension(IN));
    finalnode.push_back(VecNode);
    VecNode.reset();
    node.push_back(finalnode);
    finalnode.reset();
}

void FileOp::Write(const INTERVAL_MATRIX& IN){
    Node VecNode, finalnode;
    VecNode.SetStyle(EmitterStyle::Flow);
    for(int i = 1;i <= RowDimension(IN);i++){
        for(int j = 1;j <= ColDimension(IN);j++){
            Node InfSupNode;
            InfSupNode.SetStyle(EmitterStyle::Flow);
            InfSupNode.push_back(IN(i,j).ival.inf);
            InfSupNode.push_back(IN(i,j).ival.sup);
            VecNode.push_back(InfSupNode);
        }
    }
    finalnode.push_back("IM");
    finalnode.push_back(RowDimension(IN));
    finalnode.push_back(ColDimension(IN));
    finalnode.push_back(VecNode);
    VecNode.reset();
    node.push_back(finalnode);
    finalnode.reset();
}

void WriteNode(Node& node,const INTERVAL& IN){
    Node InfSupNode,Inode;
    InfSupNode.SetStyle(EmitterStyle::Flow);
    InfSupNode.push_back(IN.ival.inf);
    InfSupNode.push_back(IN.ival.sup);
    Inode.push_back("I");
    Inode.push_back(InfSupNode);
    node.push_back(Inode);
}

void WriteNode(Node& node,const INTERVAL_VECTOR& IN){
    Node VecNode, finalnode;
    VecNode.SetStyle(EmitterStyle::Flow);
    for(int i = 1;i <= Dimension(IN);i++){
        Node InfSupNode;
        InfSupNode.SetStyle(EmitterStyle::Flow);
        InfSupNode.push_back(IN(i).ival.inf);
        InfSupNode.push_back(IN(i).ival.sup);
        VecNode.push_back(InfSupNode);
    }
    finalnode.push_back("IV");
    finalnode.push_back(Dimension(IN));
    finalnode.push_back(VecNode);
    VecNode.reset();
    node.push_back(finalnode);
    finalnode.reset();
}

void WriteNode(Node& node,const INTERVAL_MATRIX& IN){
    Node VecNode, finalnode;
    VecNode.SetStyle(EmitterStyle::Flow);
    for(int i = 1;i <= RowDimension(IN);i++){
        for(int j = 1;j <= ColDimension(IN);j++){
            Node InfSupNode;
            InfSupNode.SetStyle(EmitterStyle::Flow);
            InfSupNode.push_back(IN(i,j).ival.inf);
            InfSupNode.push_back(IN(i,j).ival.sup);
            VecNode.push_back(InfSupNode);
        }
    }
    finalnode.push_back("IM");
    finalnode.push_back(RowDimension(IN));
    finalnode.push_back(ColDimension(IN));
    finalnode.push_back(VecNode);
    VecNode.reset();
    node.push_back(finalnode);
}

void WriteNode(Node& node,const VECTOR& IN){
    Node VecNode, finalnode;
    VecNode.SetStyle(EmitterStyle::Flow);
    for(int i = 1;i <= Dimension(IN);i++){
        Node InfSupNode;
        InfSupNode.SetStyle(EmitterStyle::Flow);
        InfSupNode.push_back(IN(i));
        VecNode.push_back(InfSupNode);
    }
    finalnode.push_back("V");
    finalnode.push_back(Dimension(IN));
    finalnode.push_back(VecNode);
    VecNode.reset();
    node.push_back(finalnode);
    finalnode.reset();
}

void WriteNode(Node& node,const MATRIX& IN){
    Node VecNode, finalnode;
    VecNode.SetStyle(EmitterStyle::Flow);
    for(int i = 1;i <= RowDimension(IN);i++){
        for(int j = 1;j <= ColDimension(IN);j++){
            Node InfSupNode;
            InfSupNode.SetStyle(EmitterStyle::Flow);
            InfSupNode.push_back(IN(i,j));
            VecNode.push_back(InfSupNode);
        }
    }
    finalnode.push_back("M");
    finalnode.push_back(RowDimension(IN));
    finalnode.push_back(ColDimension(IN));
    finalnode.push_back(VecNode);
    VecNode.reset();
    node.push_back(finalnode);
    finalnode.reset();
}
void WriteNode(Node& node,const REAL& IN){
    Node finalnode;
    finalnode.push_back("R");
    finalnode.push_back((IN));
    node.push_back(finalnode);
}

void WriteNode(Node& node,const INT& IN){
    Node finalnode;
    finalnode.push_back("i");
    finalnode.push_back((IN));
    finalnode.push_back(IN);
    node.push_back(finalnode);
}

INTERVAL_VECTOR FileOp::ReadIV(const int nodeIdx){
    INTERVAL_VECTOR out;
    if(!node.IsNull()){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "IV") return out;
            int tam = node[nodeIdx][1].as<int>();
            Resize(out,tam);
            for(int i = 0;i < tam;i++){
                out(i+1).ival.inf = node[nodeIdx][2][i][0].as<double>();
                out(i+1).ival.sup = node[nodeIdx][2][i][1].as<double>();
            }
        }
    }
    return out;
}

INTERVAL FileOp::ReadI(const int nodeIdx){
    INTERVAL out;
    if(!node.IsNull()){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "I") return out;
            out.ival.inf = node[nodeIdx][1][0].as<double>();
            out.ival.sup = node[nodeIdx][1][1].as<double>();
        }
    }
    return out;
}

INTERVAL_MATRIX FileOp::ReadIM(const int nodeIdx){
    INTERVAL_MATRIX out;
    if(!node.IsNull()){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "IM") return out;
            int nRow = node[nodeIdx][1].as<int>();
            int nCol = node[nodeIdx][2].as<int>();
            Resize(out,nRow,nCol);
            for(int i = 0;i < nRow;i++){
                for(int j = 0;j < nCol;j++){
                    out(i+1,j+1).ival.inf = node[nodeIdx][3][nRow*i+j][0].as<double>();
                    out(i+1,j+1).ival.sup = node[nodeIdx][3][nRow*i+j][1].as<double>();
                }
            }
        }
    }
    return out;
    
}

bool ReadNode(const Node& node,const int nodeIdx,INTERVAL& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "I") return false;
            std::string NumbOrInf = node[nodeIdx][1][0].as<std::string>();
            if(NumbOrInf.find("inf") != string::npos) x.ival.inf=std::stod(NumbOrInf);
            else x.ival.inf = node[nodeIdx][1][0].as<double>();
            NumbOrInf = node[nodeIdx][1][1].as<std::string>();
            if(NumbOrInf.find("inf") != string::npos) x.ival.inf=std::stod(NumbOrInf);
            else x.ival.sup = node[nodeIdx][1][1].as<double>();
            return true;
        }
    }
    return false;
}
bool ReadNode(const Node& node,const int nodeIdx,INTERVAL_VECTOR& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() > nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "IV") return false;
            int tam = node[nodeIdx][1].as<int>();
            Resize(x,tam);
            for(int i = 0;i < tam;i++){
                std::string NumbOrInf = node[nodeIdx][2][i][0].as<std::string>();
                if(NumbOrInf.find("inf") != string::npos) x(i+1).ival.inf=std::stod(NumbOrInf);
                else x(i+1).ival.inf = node[nodeIdx][2][i][0].as<double>();
                NumbOrInf = node[nodeIdx][2][i][1].as<std::string>();
                if(NumbOrInf.find("inf") != string::npos) x(i+1).ival.sup=std::stod(NumbOrInf);
                else x(i+1).ival.sup = node[nodeIdx][2][i][1].as<double>();
            }
            return true;
        }
    }
    return false;
}
bool ReadNode(const Node& node,const int nodeIdx,INT& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "i") return false;
            x = node[1][0].as<int>();
            return true;
        }
    }
    return false;
}
bool ReadNode(const Node& node,const int nodeIdx,INTERVAL_MATRIX& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "IM") return false;
            int nRow = node[nodeIdx][1].as<int>();
            int nCol = node[nodeIdx][2].as<int>();
            Resize(x,nRow,nCol);
            INT ContData = 0;
            for(int i = 0;i < nRow;i++){
                for(int j = 0;j < nCol;j++){
                    std::string NumbOrInf = node[nodeIdx][3][ContData][0].as<std::string>();
                    if(NumbOrInf.find("inf") != string::npos) x(i+1,j+1).ival.inf=std::stod(NumbOrInf);
                    else x(i+1,j+1).ival.inf = node[nodeIdx][3][ContData][0].as<double>();
                    NumbOrInf = node[nodeIdx][3][ContData][1].as<std::string>();
                    if(NumbOrInf.find("inf") != string::npos) x(i+1,j+1).ival.sup=std::stod(NumbOrInf);
                    else x(i+1,j+1).ival.sup = node[nodeIdx][3][ContData][1].as<double>();
                    ContData++;
                }
            }
            return true;
        }
    }    
    return false;
}
bool ReadNode(const Node& node,const int nodeIdx,VECTOR& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "V") return false;
            int tam = node[nodeIdx][1].as<int>();
            Resize(x,tam);
            for(int i = 0;i < tam;i++){
                std::string NumbOrInf = node[nodeIdx][2][i][0].as<std::string>();
                if(NumbOrInf.find("inf") != string::npos) x(i+1) = std::stod(NumbOrInf);
                else x(i+1) = node[nodeIdx][2][i][0].as<double>();
            }
            return true;
        }
    }
    return false;
}
bool ReadNode(const Node& node,const int nodeIdx,MATRIX& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "M") return false;
            int nRow = node[nodeIdx][1].as<int>();
            int nCol = node[nodeIdx][2].as<int>();
            Resize(x,nRow,nCol);
            int ContEl = 0;
            for(int i = 0;i < nRow;i++){
                for(int j = 0;j < nCol;j++){
                    std::string NumbOrInf = node[nodeIdx][3][ContEl][0].as<std::string>();
                    if(NumbOrInf.find("inf") != string::npos) x(i+1,j+1) = std::stod(NumbOrInf);
                    else x(i+1,j+1) = node[nodeIdx][3][ContEl][0].as<double>();
                    ContEl++;
                }
            }
            return true;
        }
    }
    return false;
}
bool ReadNode(const Node& node,const int nodeIdx,REAL& x){
    YAML::Emitter emitter;
    emitter << node;
    if(emitter.size() != 0){
        if(node.size() >= nodeIdx){
            string type = node[nodeIdx][0].as<string>();
            if(type != "R") return false;
            std::string NumbOrInf = node[nodeIdx][1].as<std::string>();
            if(NumbOrInf.find("inf") != string::npos) x = std::stod(NumbOrInf);
            else x = node[nodeIdx][1].as<double>();
            return true;
        }
    }
    return false;
}
VOID ChangeEqPower(CONST string FileName){
    fstream feq;
    ofstream fout;
    string line;
    feq.open(FileName,ios::out|ios::in);
    int contLine =0;
    if (feq.is_open()){
        while ( getline (feq,line) ){
            int Lastfound = 0;
            int found = line.find("^");
            string FoutName = "EqL" + to_string(contLine) + ".txt";
            contLine++;
            fout.open(FoutName);
            while(found != string::npos){
                int foundPar = line.find_last_of(")",found);
                if(foundPar != string::npos){
                    int contFecha = 1,contPos;
                    if(line.at(found+1) == '(')
                        cout << line.substr(contPos,foundPar-contPos) << endl;
                    for(contPos = foundPar-1;contFecha != 0;contPos--){
                        if(line.at(contPos) == ')')
                            contFecha++;
                        if(line.at(contPos) == '(')
                            contFecha--;
                    }
                    int POW;
                    if(line.at(found+1) != '('){
                        POW = stoi(line.substr(found+1,1));
                        switch(POW){
                            case 2:
                                line.erase(found,2);
                                if(line.at(found-1) != ')')
                                    line.insert(found,")");
                                if(line.at(contPos+1) != '(')
                                    line.insert(contPos+1,"Sqr(");
                                else
                                    line.insert(contPos+1,"Sqr");
                                break;
                            default:
                                string tmpPower = "," + to_string(POW);
                                line.erase(found,2);
                                if(line.at(contPos-1) != ')')
                                    line.insert(found-1,")"+tmpPower);
                                else
                                    line.insert(found-1,tmpPower);
                                for(;line.at(contPos) != '/' && line.at(contPos) != '*' && line.at(contPos) != ' ';contPos--);
                                if(line.at(contPos+1) != '(')
                                    line.insert(contPos+1,"Power(");
                                else
                                    line.insert(contPos+1,"Power");
                        }
                    }
                    else{
                        cout << "line.substr(contPos+1,found-contPos+1)=" << line.substr(contPos+1,found-(contPos-5)) << endl;
                        if(line.at(found+2) == '1'){
                            line.erase(found,6);
                            line.insert(contPos+1,"Sqrt");
                        }
                        if(line.at(found+2) == '3'){
                            line.erase(found,6);
                            line.insert(found-1,",3)");
                            line.insert(contPos+1,"Sqrt(Power");                            
                        }
                        cout << "line.substr(contPos+1,found-contPos+1)=" << line.substr(contPos+1,found-(contPos-5)) << endl;
                    }
                }
                Lastfound = found;
                found = line.find("^",found+1);
            }
            fout << line << endl;
            fout.close();
        }
        feq.close();
    }
}
void delete_folder_tree (const char* directory_name) {
    DIR*            dp;
    struct dirent*  ep;
    char            p_buf[512] = {0};

    dp = opendir(directory_name);

    while ((ep = readdir(dp)) != NULL) {
        string dirname = ep->d_name;
        if(dirname != "." && dirname != ".."){
            snprintf(p_buf,512, "%s/%s", directory_name, ep->d_name);
            if (path_is_directory(p_buf))
                delete_folder_tree(p_buf);
            else
                remove(p_buf);
        }
    }

    closedir(dp);
}
int path_is_directory (const char* path) {
    struct stat s_buf;

    if (stat(path, &s_buf))
        return 0;

    return S_ISDIR(s_buf.st_mode);
}
bool file_exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
std::vector<string> ListFiles(const char* directory_name,string extension){
    std::vector<string> filenames;
    DIR*            dp;
    struct dirent*  ep;
    char            p_buf[512] = {0};
    string filename;

    dp = opendir(directory_name);

    while ((ep = readdir(dp)) != NULL) {
        string dirname = ep->d_name;
        if(dirname != "." && dirname != ".."){
            snprintf(p_buf,512, "%s/%s", directory_name, ep->d_name);
            if (!path_is_directory(p_buf)){
                filename = p_buf;
                if(filename.find(extension) != string::npos){
                    if(filename.find("~") != string::npos)continue;
                    if(filename.find("cópia") != string::npos)continue;
                    int idx = filename.find_last_of("/");
                    filename = filename.substr(idx+1);
                    filenames.push_back(filename);
                }
            }
        }
    }

    closedir(dp);
    return filenames;
}
string ChooseFile(std::vector<string> filenames){
    string out;
//    if(filenames.empty()){
//        cerr << "No txt file on directory" << endl;
//        return out;
//    }
//    for(int i = 0;i < filenames.size();i++){
//        cout << i << "->" << filenames[i] << endl;
//    }
//    INT selection = INT_MAX;
//    cout << "Choose one file by number (-1 to go out without file name): ";
//    cout.flush();
//    while(selection > filenames.size()){
//        cin >> selection;
//        if(selection < 0)break;
//    }
//    if(selection >= 0)
//        return filenames[selection];
    return out;
}
std::vector<string> ListAllFiles(const char* directory_name,string filenamein){
    std::vector<string> filenames;
    DIR*            dp;
    struct dirent*  ep;
    char            p_buf[512] = {0};
    string filename;

    dp = opendir(directory_name);

    while ((ep = readdir(dp)) != NULL) {
        string dirname = ep->d_name;
        if(dirname != "." && dirname != ".."){
            snprintf(p_buf,512, "%s/%s", directory_name, ep->d_name);
            if (!path_is_directory(p_buf)){
                filename = p_buf;
                if(filename.find(filenamein) != string::npos){
                    if(filename.find("~") != string::npos)continue;
                    filenames.push_back(filename);
                }
            }else{
                std::vector<string> retorno;
                retorno = ListAllFiles(p_buf,filenamein);
                for(std::vector<string>::iterator it = retorno.begin();
                        it != retorno.end();it++)
                    filenames.push_back((*it));
            }
        }
    }
    closedir(dp);
    return filenames;    
}
void SaveMtrxFiles(string loadfilename,string savefilename,string CAMID){
    FileOp mtrxnode(loadfilename,ios::in);
    YAML::Node tmpnode = mtrxnode.node[CAMID];
    YAML::Emitter emitter;
    emitter << tmpnode;
    if(emitter.size() == 0)return;
    for(int contEtapa = 0;;contEtapa++){
        YAML::Node datanode = mtrxnode.node[CAMID][contEtapa];
        YAML::Emitter emtt;
        emtt << datanode;
        if(emtt.size() == 0)break;
        Node elementnode;
        INTERVAL_MATRIX RRt;
        elementnode = datanode["RRtFinal"][0];
        if(!ReadNode(elementnode,0,RRt)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        INTERVAL_MATRIX K;
        elementnode = datanode["KAAdj"][0];
        if(!ReadNode(elementnode,0,K)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        INTERVAL_VECTOR t;
        elementnode = datanode["tAAdj"][0];
        if(!ReadNode(elementnode,0,t)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        INTERVAL_VECTOR EulAng;
        elementnode = datanode["EulAnglAAdj"][0];
        if(!ReadNode(elementnode,0,EulAng)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        REAL tardiam;
        elementnode = datanode["tardiam"][0];
        if(!ReadNode(elementnode,0,tardiam)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        REAL imgdiam;
        elementnode = datanode["imgdiam"][0];
        if(!ReadNode(elementnode,0,imgdiam)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        REAL tarnoise;
        elementnode = datanode["tarnoise"][0];
        if(!ReadNode(elementnode,0,tarnoise)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        REAL imgnoise;
        elementnode = datanode["imgnoise"][0];
        if(!ReadNode(elementnode,0,imgnoise)){
            elementnode.reset();
            continue;
        }
        elementnode.reset();
        int Idx = loadfilename.find_last_of("/");
        string filename = loadfilename.substr(0,Idx+1) + savefilename;
        ofstream csvcamdata(filename.c_str());
        csvcamdata << "PxDiam,TarDiam,PxNoise,TarNoise,RRt(:,1),RRt(:,2),RRt(:,3),RRt(:,4),K(:,1),";
        csvcamdata << "K(:,2),K(:,3),EulAng(1),EulAng(2),EulAng(3),t(1),t(2),t(3)" << endl;
        for(int i = 1;i <= 3;i++){
            csvcamdata << imgdiam << "," << tardiam << "," << imgnoise << "," << tarnoise << ",";
            csvcamdata << RRt(i,1).inf() << "," << RRt(i,1).sup() << "," << RRt(i,2).inf() << "," << RRt(i,2).sup() << ",";
            csvcamdata << RRt(i,3).inf() << "," << RRt(i,3).sup() << "," << RRt(i,4).inf() << "," << RRt(i,4).sup() << ",";
            csvcamdata << K(i,1).inf() << "," << K(i,1).sup() << "," << K(i,2).inf() << "," << K(i,2).sup() << ",";
            csvcamdata << t(1).inf() << "," << t(1).sup() << "," << t(2).inf() << t(2).sup() << "," << t(3).inf() << t(3).sup() << ",";
            csvcamdata << endl;
        }
        csvcamdata.close();
    }
    return;
}