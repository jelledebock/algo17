#include <cstdlib>
#include <iostream>
#include <cassert>
#include <stack>
#include <functional>
#include <memory>
#include <queue>
using namespace std;

template <class T>
class Binboom;

template <class T>
class Binknoop;

template<class T>
using Binknoopptr=std::unique_ptr<Binknoop<T> >;



template <class T>
class Binboom:public Binknoopptr<T>{
    public:
        using std::unique_ptr<Binknoop<T> >::unique_ptr;
        friend istream& operator>>(istream& is, Binboom<T>& bb){
            return bb.lees(is);
        }
        friend ostream& operator<<(ostream& os, const Binboom<T>& bb){
            return bb.schrijflevelorder(os);
        }
//schrijf schrijft uit in een vorm die min of meer menselijk leesbaar is
        ostream& schrijf(ostream&);
        int aantalSleutels() const;
        istream& lees(istream&);
//schrijflevelorder schrijft uit in een vorm die door lees(...) kan gelezen worden.
        ostream& schrijflevelorder(ostream& os) const;
        void DEbezoek(std::function<void(T&&)>, std::function<void(T&&)>, std::function<void(T&&)>);
        Binboom<T>& operator=(Binboom<T> && other){
            std::unique_ptr<Binknoop<T> >::operator=(std::move(other));
            return *this;
        }
        Binboom() : Binknoopptr <T>(nullptr){};
        ~Binboom(){ this->release(); };
    private:
        void addNode(Binknoop<T> * node, bool left, int index, vector<T> sleutels, vector<int> linkerburen, vector<int> rechterburen);
};

template <class T>
istream & Binboom<T>::lees(istream & input) {
    int aantal_nodes;
    input>>aantal_nodes;
    vector<bool> parents(aantal_nodes,false);
    vector<int> linkerBuren(aantal_nodes,-1);
    vector<int> rechterBuren(aantal_nodes, -1);
    vector<T> sleutels(aantal_nodes);

    int knoopIndex = 0;

    while(!input.eof()){
        T sleutel;
        int nr1;
        int nr2;

        input>>sleutel;
        input>>nr1;
        input>>nr2;

        sleutels[knoopIndex]=sleutel;

        if(nr1!=-1){
            parents[nr1]=true;
            linkerBuren[knoopIndex]=nr1;
        }
        if(nr2!=-1){
            parents[nr2]=true;
            rechterBuren[knoopIndex]=nr2;
        }
        knoopIndex++;
    }

    //Bepaal wortel
    int i=0;
    while(i<aantal_nodes && parents[i]==true){
        i++;
    }
    if(parents[i]==false){
        Binknoop<T> * temp = new Binknoop<T>();
        temp->sl = sleutels[i];
        Binknoopptr<T> nieuw(temp);

        *this=std::move(nieuw);

        addNode(this->get(), true, linkerBuren[i], sleutels, linkerBuren, rechterBuren);
        addNode(this->get(), false, rechterBuren[i], sleutels, linkerBuren, rechterBuren);
    }

    return input;
}
template <class T>
void Binboom<T>::addNode(Binknoop<T> * node, bool left, int index, vector<T> sleutels, vector<int> linkerburen, vector<int> rechterburen){
    if(index!=-1){
        Binknoop<T> * temp = new Binknoop<T>();
        temp->sl = sleutels[index];

        Binknoopptr<T> nieuw(temp);
        Binboom<T> kind;
        kind = std::move(nieuw);

        if(left){
            node->links=std::move(kind);
            addNode(node->links.get(), true, linkerburen[index], sleutels, linkerburen, rechterburen);
            addNode(node->links.get(), false, rechterburen[index], sleutels, linkerburen, rechterburen);
        }
        else{
            node->rechts=std::move(kind);
            addNode(node->rechts.get(), true, linkerburen[index], sleutels, linkerburen, rechterburen);
            addNode(node->rechts.get(), false, rechterburen[index], sleutels, linkerburen, rechterburen);
        }
    }
}

template<class T>
int Binboom<T>::aantalSleutels() const{
    if (!*this)
        return 0;
    else
        return (*this)->links.aantalSleutels()+(*this)->rechts.aantalSleutels() + 1;
}


template<class T>
ostream& Binboom<T>::schrijflevelorder(ostream& os) const{
    if ((*this)){
        os<<aantalSleutels()<<endl;
        queue<Binknoop<T> * > ATW;//Af Te Werken knopen
        ATW.push(this->get());
        int kindnr=1;
        Binknoop<T>* nuknoop=ATW.front();
        while (nuknoop!=0){
            os<<nuknoop->sl<<' ';
            if (!nuknoop->links)
                os<<"-1 ";
            else{
                os<<kindnr++<<' ';
                ATW.push(nuknoop->links.get());
            }
            if (!nuknoop->rechts)
                os<<"-1\n";
            else{
                os<<kindnr++<<'\n';
                ATW.push(nuknoop->rechts.get());
            }
            ATW.pop();
            if (ATW.front()!=0)
                nuknoop=ATW.front();
            else
                nuknoop=0;
        }
    }
    return os;
}
template<class T>
ostream& Binboom<T>::schrijf(ostream& os){
    if ((*this)!=0){
        os<<"sleutel: "<<(*this)->sl<<" linkerkind: ";
        if ((*this)->links)
            os<<(*this)->links->sl;
        else
            os<<"(geen)";
        os<<" rechterkind: ";
        if ((*this)->rechts)
            os<<(*this)->rechts->sl;
        else
            os<<"(geen)";
        os<<endl;
        (*this)->links.schrijf(os);
        (*this)->rechts.schrijf(os);
    }
    return os;
}

template<class T>
void Binboom<T>::DEbezoek(function<void(T&&)>preorder,
                          function<void(T&&)>inorder,
                          function<void(T&&)>postorder){
    stack<pair<Binknoop<T> *,int > >ATW;//ATW: Af Te Werken
    if ((*this)!=0){
        ATW.emplace((*this).get(),1);
        while (!ATW.empty()){
            Binknoop<T> * nuknoop=ATW.top().first;
            int pass=ATW.top().second;
            ATW.top().second++;
            switch (pass){
                case 1:
                    preorder(move(nuknoop->sl));
                    if (nuknoop->links)
                        ATW.emplace(nuknoop->links.get(),1);
                    break;
                case 2:
                    inorder(move(nuknoop->sl));
                    if (nuknoop->rechts)
                        ATW.emplace(nuknoop->rechts.get(),1);
                    break;
                case 3:
                    postorder(move(nuknoop->sl));
                    ATW.pop();
            }
        };
    };
}

template <class T>
class Binknoop{
    friend class Binboom<T>;
private:
    T sl;
    Binboom<T> links,rechts;
};

