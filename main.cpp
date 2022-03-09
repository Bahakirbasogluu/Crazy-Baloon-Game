#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
//These two variables declared top because I did not want to recall them in func or as an argument.
vector<int> vectorInt;
int point;
//This method prints the last version of table.
void printingTable(int** table,int n, ofstream& out){
    for(int i = 0 ; i<n ; i = i+1){
        for(int j = 0 ; j<n ; j = j+1){
            out<<table[i][j]<<" ";
        }
        out<<endl;
    }}
//This method check all four around of a cell
void aroundCellCheck(int** table, int n , int row,int column ,int value,int previousRow, int previousColumn){
    if(row - 1 >=0){
        if((table[row-1][column] == value) && (row-1 != previousRow )){
            vectorInt.emplace_back(row-1);      vectorInt.emplace_back(column);
        }}
    if(row+1<n){
        if(table[row+1][column] == value && (row+1 != previousRow  )){
            vectorInt.emplace_back(row+1);      vectorInt.emplace_back(column);
        }}
    if(column-1>=0){
        if(table[row][column-1]==value&&(column-1 !=previousColumn)){
            vectorInt.emplace_back(row);        vectorInt.emplace_back(column-1);
        }}
    if(column+1<n){
        if(table[row][column+1]==value&&( column+1 !=previousColumn)){
            vectorInt.emplace_back(row);        vectorInt.emplace_back(column+1);
        }}}
//The functions for looking 4 sides of a cell.
void upCellCheck(int** table, int n , int row,int column ,int value,int previousRow){
    if(row - 1 >=0){
        if((table[row-1][column] == value) && (row-1 != previousRow  )){
            vectorInt.emplace_back(row-1);       vectorInt.emplace_back(column);
            aroundCellCheck(table,n,row-1,column,value,row,column);
        }}}
void downCellCheck(int** table, int n , int row,int column ,int value,int previousRow)
{
    if(row+1<n){
        if(table[row+1][column] == value && (row+1 != previousRow  )){
            vectorInt.emplace_back(row+1);      vectorInt.emplace_back(column);
            aroundCellCheck(table,n,row+1,column,value,row,column);
        }}}
void leftCellCheck(int** table, int n , int row,int column ,int value, int previousColumn){
    if(column-1>=0){
        if(table[row][column-1]==value&&(column-1 !=previousColumn)){
            vectorInt.emplace_back(row);        vectorInt.emplace_back(column-1);
            aroundCellCheck(table,n,row,column-1,value,row,column);
        }}}
void rightCellCheck(int** table, int n , int row,int column ,int value, int previousColumn){
    if(column+1<n){
        if(table[row][column+1]==value&&( column+1 !=previousColumn)){
            vectorInt.emplace_back(row);        vectorInt.emplace_back(column+1);
            aroundCellCheck(table,n,row,column+1,value,row,column);
        }}}
int** leftDownCellCheck(int** table, int row, int column, int value, int size){
    //here is looking down right
    if(size>row &&  column>=0 ){
        if(value == table[row][column]){
            table[row][column] = 0 ;
            point = point + value;
        }}
    else { return table; }
    return leftDownCellCheck(table, row+1, column-1, value, size );
}
int** rightUpCellCheck(int** table, int row, int column, int value, int size){
    //here is looking down right
    if(row>=0 && size > column ){
        if(value == table[row][column]){
            table[row][column] = 0 ;
            point = point + value;
        }}
    else { return table; }
    return rightUpCellCheck(table, row-1, column+1, value, size );
}
int** rightDownCellCheck(int** table, int row, int column, int value, int size){
    //here is looking down right
    if(size> row && size > column ){
        if(value == table[row][column]){
            table[row][column] = 0 ;
            point = point + value;
        }}
    else { return table; }
    return rightDownCellCheck(table, row+1, column+1, value, size );
}
int** leftUpCellCheck(int** table, int row, int column, int value, int size){
    //here is looking up left
    if(row>=0 && column >=0){
        if(value == table[row][column]){
            table[row][column] = 0 ;
            point = point + value;
        }}
    else { return table; }
    return leftUpCellCheck(table, row-1 , column-1, value, size );
}
int** upDownLeftRightCellCheck(int** table , int row , int column , int value , int size){
    if(size == 0){
        return table;
    }
    //here is looking right and left
    if(value == table[row][size-1]){
        table[row][size-1] = 0 ;
        point = point +value;
    }
    //here is looking up and down
    if(value == table[size-1][column]){
        table[size-1][column] = 0 ;
        point = point +value;
    }
    return upDownLeftRightCellCheck(table,row,column,value,size-1);
}
//These methods create a table and returns table to main
int** creatingZeroTable(int** table , int n){
    table = new int*[n];
    for(int i = 0 ; i<n ; i=i+1){
        table[i] = new int[n];
    }
    for(int i = 0 ; i<n ; i=i+1){
        for(int j = 0 ; j<n ; j=j+1){
            table[i][j] = 0 ;
        }}
    return table;
}
int** creatingTable(int** table, int m,vector<string> vectorString2){
    table = new int*[m];
    int counter1 = 0 , counter2 = 0 ;
    for(int i = 0 ; i<m ; i = i +1){
        table[i] = new int[m];
    }
    for(int i = 0 ; i<(m*m + (m-1)); i = i+1){
        if(vectorString2[i]==" "){
            counter1 = counter1 +1;
            counter2 = 0;
            continue;
        }
        table[counter1][counter2] = stoi(vectorString2[i]);
        counter2 = counter2 +1;
    }
    return table;
}
//These methods fill the vector from file which has been reading
vector<string> fileReadVectorFill(const string& fileName,vector<string> v){
    ifstream input1(fileName);
    for (string line; getline(input1, line); )
    {
        string delimiter = " ";
        size_t pos;     string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            v.emplace_back(token);
            line.erase(0, pos + delimiter.length());
        }
        v.emplace_back(line);
        v.emplace_back(" ");
    }
    return v;
}
vector<string> fileReadVectorFill2(const string& fileName, vector<string> v){
    ifstream input2(fileName);
    for (string line; getline(input2, line); )
    {
        string delimiter = " ";
        size_t pos;     string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            v.emplace_back(token);
            line.erase(0, pos + delimiter.length());
        }
        v.emplace_back(line);
        v.emplace_back(" ");
    }
    return v;
}
//Clearing the main func for more understandable code / cause of that write a func that calls others
void funcCalling(int** table, int n , int row,int column ,int value,int previousRow){
    rightCellCheck(table,n,row,column,value,previousRow);
    leftCellCheck(table,n,row,column,value,previousRow);
    upCellCheck(table,n,row,column,value,previousRow);
    downCellCheck(table,n,row,column,value,previousRow);
}
int** funcCalling2(int** table , int row , int column , int value , int size){
    table = upDownLeftRightCellCheck(table,row,column,value,size);
    table = rightDownCellCheck(table,row,column,value,size);
    table = leftUpCellCheck(table,row,column,value,size);
    table = leftDownCellCheck(table,row,column,value,size);
    table = rightUpCellCheck(table,row,column,value,size);
    return table;
}
//Clearing vector
vector<string> vectorErasing(vector<string> vector , int numberOfErasing ){
    if(numberOfErasing == 0){
        return vector;
    }
    vector.erase(vector.begin());
    return vectorErasing(vector,numberOfErasing-1);
}

int main(__attribute__((unused)) int argc, char *argv[]) {

    //This is my vector to push strings from first,second input file
    vector<string> vectorString1;           vector<string> vectorString2;
    //giving the name of first,second txt file
    string input1 = argv[1];           string input2 = argv[2];     ofstream out(argv[3]);
    //updating vector with method
    vectorString1 = fileReadVectorFill(input1, vectorString1);           vectorString2 = fileReadVectorFill2(input2,vectorString2);
    //deleting last free item
    vectorString1.pop_back();     vectorString2.pop_back();
    // sizePart1 = size of array
    int sizePart1 = stoi(vectorString1[0]);                            int sizePart2 = stoi(vectorString2[0]);
    vectorString1 = vectorErasing(vectorString1,1);     vectorString2 = vectorErasing(vectorString2,2);
    // initializing general tablePart1
    int **tablePart1 = nullptr , **tablePart2 = nullptr;
    // creating these tables for the game. tablePart1 is fully zero in the beginning. tablePart2 is given in the input2.
    tablePart1 = creatingZeroTable(tablePart1, sizePart1);
    tablePart2 = creatingTable(tablePart2, sizePart2, vectorString2);
    vectorString2 = vectorErasing(vectorString2,(sizePart2 * sizePart2 + (sizePart2)));
    //This is how I update the indexes
    //also this is part1
    for(int i = 0 ; i < vectorString1.size() ; i++){
        if(vectorString1[i] == " "){
            funcCalling(tablePart1, sizePart1, stoi(vectorString1[i + 2]), stoi(vectorString1[i + 3]), stoi(vectorString1[i + 1]), -1);
            tablePart1[stoi(vectorString1[i + 2])][stoi(vectorString1[i + 3])] = stoi(vectorString1[i + 1]);
        }
        while (vectorInt.size()/2 > 1){
            tablePart1[stoi(vectorString1[i + 2])][stoi(vectorString1[i + 3])] +=1;
            for(int j = 0 ; j <vectorInt.size() ; j = j+2){
                tablePart1[vectorInt[j]][vectorInt[j + 1]] = 0;
            }
            vectorInt.clear();
            funcCalling(tablePart1, sizePart1, stoi(vectorString1[i + 2]), stoi(vectorString1[i + 3]), tablePart1[stoi(vectorString1[i + 2])][stoi(vectorString1[i + 3])], -1);
        }
        vectorInt.clear();
    }
    //printing the final of part1
    out<<"PART 1:"<<endl;
    printingTable(tablePart1, sizePart1,out);
    //part2
    for(int i = 0 ; i<vectorString2.size() ; i = i+3){
        tablePart2 = funcCalling2(tablePart2, stoi(vectorString2[i]), stoi(vectorString2[i + 1]), tablePart2[stoi(vectorString2[i])][stoi(vectorString2[i + 1])], sizePart2);
    }
    out<<endl<<"PART 2:"<<endl;
    printingTable(tablePart2, sizePart2,out);
    out<< "Final Point: "<<point<<"p"<<endl;
    out.close();
}