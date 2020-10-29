#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Individual{
private:
    string class_name;
    double a,b,c,d;
public:
    Individual(double a, double b, double c, double d, string class_name=""){
        this->class_name = class_name;
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
    string Get_nameclass(){
        return class_name;
    }
    void Set_name_class(string class_name){
        this->class_name = class_name;
    }
    double Geta(){
        return a;
    }
    double Getb(){
        return b;
    }
    double Getc(){
        return c;
    }
    double Getd(){
        return d;
    }
};

double Calc_euclidesdist(Individual *one, Individual *two){
    double soma = (pow(one->Geta() - two->Geta(), 2) + 
                   pow(one->Getb() - two->Getb(), 2) + 
                   pow(one->Getc() - two->Getc(), 2) +
                   pow(one->Getd() - two->Getd(), 2));

    return sqrt(soma);
}

string Knn_algorithm(vector<Individual> vet, Individual entrada_a_decidir, int k){
    //checar se k é impar
    if(k % 2 == 0){
        k--;
        if(k<=0){
            k = 1;
        }
    }
    //calcular as distancias e ordenar do menor para o maior
    set<pair<double, int>> Individual_dist;

    for(int i=0;i<vet.size();i++){
        double dist = Calc_euclidesdist(&vet[i], &entrada_a_decidir);
        Individual_dist.insert(make_pair(dist, i));
    }
    //pegar os k menores
    vector<int> cont_k(3,0);
    int till_k = 0;
    set<pair<double, int>>::iterator Individual_it;
    for(Individual_it = Individual_dist.begin();Individual_it != Individual_dist.end();Individual_it++){
        if(vet[Individual_it->second].Get_nameclass() == "Iris-setosa"){

            cont_k[0]++;
        }
        else if(vet[Individual_it->second].Get_nameclass() == "Iris-versicolor"){
            cont_k[1]++;
        }
        else{
            cont_k[2]++;
        }
        if(till_k > k) break;
        till_k++;
        
    }
    //escolher o nome da classe
    string result;
    if(cont_k[0] >= cont_k[1] && cont_k[0] >= cont_k[2]){
        result = "Iris-setosa";
        return result;
    }
    else if(cont_k[1] >= cont_k[0] && cont_k[1] >= cont_k[2]){
        result = "Iris-versicolor";
        return result;
    }
    else{
        result = "Iris-virginica";
        return result;
    }
}

int main(){

    vector<Individual> data_set;
    int max_data = 150;
    int qtd_training = 100;

    Individual *enter_dataset;

    for(int i=0;i<qtd_training;i++){
        float a,b,c,d;
        string class_name;
        cin >> a >> b >> c >> d >> class_name;
        enter_dataset = new Individual(a, b, c, d, class_name);
        data_set.push_back(*enter_dataset);
    }

    int qtd_acertos=0;
    int k = 10;

    for(int i=0;i<max_data - qtd_training;i++){
        float a,b,c,d;
        string class_name;
        cin >> a >> b >> c >> d >> class_name;
        enter_dataset = new Individual(a, b, c, d);
        string try_classname = Knn_algorithm(data_set, *enter_dataset, k);
        if(try_classname == class_name){
            qtd_acertos++;
        }
    }

    cout << "a quantidade de acertos para a quantidade de tentativas: " << qtd_acertos << " " << max_data - qtd_training << endl;

    return 0;
}
