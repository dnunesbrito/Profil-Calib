/* 
 * File:   FileOp.h
 * Author: darlan
 *
 * Created on 21 de Janeiro de 2016, 12:42
 */
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Vector.h>
#include <IntervalVector.h>
#include <Matrix.h>
#include <IntervalMatrix.h>
#include <Functions.h>
#include <Utilities.h>
#include <Interval.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <IntegerVector.h>
#include <yaml-cpp/yaml.h>


#ifndef FILEOP_H
#define	FILEOP_H

using namespace std;
using namespace YAML;

class FileOp {
public:
    fstream SaveFile;
    Node node;
    FileOp();
    FileOp(const FileOp& orig);
    FileOp(const string& );
    FileOp(const string& Filename,const ios::openmode& filemode);
    virtual ~FileOp();
    void Write(const INTERVAL&);
    void Write(const INTERVAL_VECTOR&);
    void Write(const INTERVAL_MATRIX&);
    INTERVAL_VECTOR ReadIV(const int nodeIdx);
    INTERVAL ReadI(const int nodeIdx);
    INTERVAL_MATRIX ReadIM(const int nodeIdx);
    FileOp operator = (const FileOp& src);
    bool IsOpen(){return isopen;}
    void close();
    friend void WriteNode(Node& ,const INTERVAL&);
    friend void WriteNode(Node& ,const INTERVAL_VECTOR&);
    friend void WriteNode(Node& ,const INTERVAL_MATRIX&);
    friend void WriteNode(Node& ,const VECTOR&);
    friend void WriteNode(Node& ,const MATRIX&);
    friend void WriteNode(Node& ,const REAL&);
    friend void WriteNode(Node& ,const INT&);
    friend bool ReadNode(const Node& ,const int, INTERVAL&);
    friend bool ReadNode(const Node& ,const int, INTERVAL_VECTOR&);
    friend bool ReadNode(const Node& ,const int, INT&);
    friend bool ReadNode(const Node& ,const int, INTERVAL_MATRIX&);
    friend bool ReadNode(const Node& ,const int, VECTOR&);
    friend bool ReadNode(const Node& ,const int, MATRIX&);
    friend bool ReadNode(const Node& ,const int, REAL&);
private:
    string FileName;
    bool isopen;
    ios::openmode mode;
};

void WriteNode(Node& ,const INTERVAL&);
void WriteNode(Node& ,const INTERVAL_VECTOR&);
void WriteNode(Node& ,const INTERVAL_MATRIX&);
void WriteNode(Node& ,const VECTOR&);
void WriteNode(Node& ,const MATRIX&);
void WriteNode(Node& ,const REAL&);
void WriteNode(Node& ,const INT&);

bool ReadNode(const Node& ,const int,INTERVAL&);
bool ReadNode(const Node& ,const int,INTERVAL_VECTOR&);
bool ReadNode(const Node& ,const int,INT&);
bool ReadNode(const Node& ,const int,INTERVAL_MATRIX&);
bool ReadNode(const Node& ,const int,VECTOR&);
bool ReadNode(const Node& ,const int,MATRIX&);
bool ReadNode(const Node& ,const int,REAL&);
VOID ChangeEqPower(CONST string FileName);
std::vector<string> ListFiles(const char* directory_name,string extension);
string ChooseFile(std::vector<string> filenames);
bool file_exists (const std::string& name);
std::vector<string> ListAllFiles(const char* directory_name,string filenamein);
void SaveMtrxFiles(string loadfilename,string savefilename,string CAMID);
//void LoadGtkListStore(CONST std::string& filename,GtkListStore *liststore,GtkListStore *colunmnames);
//void LoadGtkListStoreIDs(CONST std::string& blenderfilename,GtkListStore *liststore);
//void SaveGtkListStore(CONST std::string& filename,GtkListStore *liststore,GtkListStore *columnnames);
void delete_folder_tree (const char* directory_name);
int path_is_directory (const char* path);
#endif	/* FILEOP_H */

