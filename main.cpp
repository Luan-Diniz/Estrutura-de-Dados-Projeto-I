#include <iostream>
#include <fstream>
#include <string>
#include "./linked_stack.h"
#include "./linked_queue.h"
using namespace std;

bool stack_verification (int pos, std::string linha, structures::LinkedStack<std::string> &pilha, structures::LinkedQueue<string> &png_info);
void file_verification(string arquivo, structures::LinkedQueue<string> &png_info);

typedef struct {
    int x;
    int y;
} coordenadas;

int main() {
    structures::LinkedStack<string> pilha;   
    structures::LinkedQueue<string> png_info; 
    string line;
    bool error = false;
    char xmlfilename[100];
    


    cin >> xmlfilename;  // entrada

    ifstream xmlfile;
    xmlfile.open(xmlfilename);

    if (xmlfile.is_open()) {
        while (!xmlfile.eof() && !error) {
            getline(xmlfile,line);
            if (line[0] == '0' || line[0] == '1') {
                continue;
            }
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '<') {
                    error = stack_verification(i, line, pilha, png_info);   // Checa o que vai fazer com relacao a pilha :D
                }
            }
        }
        xmlfile.close();
    } else {
        throw out_of_range("Arquivo xml não existente");
    }

    if (!pilha.empty()) {
        error = true;
    }
    
    if (!error) {  //Exercicio 2
        file_verification(xmlfilename, png_info);
    } else {
        cout << "error" << std::endl;
    }

    return 0;
}

bool stack_verification (int pos, string linha, structures::LinkedStack<string> &pilha, structures::LinkedQueue<string> &png_info) {
    bool deu_erro = false;
    int pos_fim = pos;
    while (linha[pos_fim] != '>') {
        pos_fim++;
    }
    if (linha[pos+1] != '/') {
        string result = linha.substr(pos+1, pos_fim-pos-1);
        pilha.push(result);
        if (result.compare("height") == 0 || result.compare("width") == 0 || result.compare("name") == 0) {    
            int pos_fim_fim = pos_fim;
            while (linha[pos_fim_fim] != '<') {
                pos_fim_fim++;
            }
            string data = linha.substr(pos_fim+1, pos_fim_fim-pos_fim-1);
            png_info.enqueue(data);                       //Vai sair nome,altura e largura nessa ordem. (FIFO)
        }
        
    } else {
        string result = linha.substr(pos+2, pos_fim-pos-2);
        string comp = pilha.pop();
        if (comp.compare(result) != 0) {
            deu_erro = true;
        }
    }
    return deu_erro;
}

void file_verification(string arquivo, structures::LinkedQueue<string> &png_info) {
    structures::LinkedQueue<coordenadas> fila; 
    ifstream xmlarquivo;
    xmlarquivo.open(arquivo);

    string png_name;
    string linha;
    int height;
    int width;
    int label;

    while (!png_info.empty()) {
        label = 0;
        png_name = png_info.dequeue();
        height = stoi(png_info.dequeue());
        width = stoi(png_info.dequeue());

        int **E;
        int **R;
        E = new int * [height];
        R = new int * [height];

        for (int i = 0; i < height; i++) {
            E[i] = new int[width];
            R[i] = new int[width];
        }
        
        getline(xmlarquivo,linha);
        while ((linha[0] != '0' && linha[0] != '1') ) {
            getline(xmlarquivo,linha);
        }
        
        int i = 0;
        while (linha[0] == '0' || linha[0] == '1') {
            for (int j = 0; j < linha.length(); j++) {
                E[i][j] = (int)linha[j] - 48;
                R[i][j] = 0;
            } 
            getline(xmlarquivo,linha);
            i++;
        }
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                //if novo componente conexo => fila.enqueue()
                if (E[i][j] == 1 && R[i][j] == 0) {
                    coordenadas aux;
                    aux.x = i;
                    aux.y = j;
                    fila.enqueue(aux);
                    label = label + 1;
                    R[i][j] = label;
                
                    while(!fila.empty()) {
                        coordenadas aux;
                        coordenadas ponto = fila.dequeue();
                        R[ponto.x][ponto.y] = label;    
                        
                        if (ponto.x > 0) {
                            if (E[ponto.x - 1][ponto.y] == 1 && R[ponto.x - 1][ponto.y] == 0) {
                                aux.x =  ponto.x - 1;
                                aux.y =  ponto.y;
                                fila.enqueue(aux);
                                R[aux.x][aux.y] = label;
                            }
                        }
                        if (ponto.x < height - 1) {
                            if (E[ponto.x + 1][ponto.y] == 1 && R[ponto.x + 1][ponto.y] == 0) {
                                aux.x =  ponto.x + 1;
                                aux.y =  ponto.y; 
                                fila.enqueue(aux);
                                R[aux.x][aux.y] = label;
                            }
                        }
                        if (ponto.y > 0) {
                            if (E[ponto.x][ponto.y - 1] == 1 && R[ponto.x][ponto.y - 1] == 0) {
                                aux.x = ponto.x;
                                aux.y = ponto.y - 1;
                                fila.enqueue(aux);
                                R[aux.x][aux.y] = label;
                            }
                        }
                        if (ponto.y < width - 1) {
                            if (E[ponto.x][ponto.y + 1] == 1 && R[ponto.x][ponto.y + 1] == 0) {
                                aux.x = ponto.x;
                                aux.y = ponto.y + 1;
                                fila.enqueue(aux); 
                                R[aux.x][aux.y] = label;
                            }
                        }
                    }
                }
            }
        }

        // deleta a matriz.
        for (int i = 0; i < height; i++) {
            delete[] E[i];
            delete[] R[i];
        }
        delete[] E;
        delete[] R; 

        cout << png_name <<" "<< label << endl;
    }

    xmlarquivo.close();
}
