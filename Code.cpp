#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

ofstream output;

class node {
	public :
		char trans;
		string from, to ; 
		node *next ;
		node (){
			next = NULL;
		}
};
class nfatransitions {
	node *head ; 
	public : 
	nfatransitions (){
		head = NULL ;
	}
	
	node *returnhead (){
			return head ;
		}
	
	void insertion (string from, string to, char trans ){
			node *temp = new node ;
			temp->from=from ;
			temp->to=to;
			temp->trans=trans; 
			if (head == NULL){
				head = temp;
				return;
			}
			node *temp1= head;
			while (temp1->next){
				temp1=temp1->next;
			}
			temp1->next= temp;
			return; 
		}
		
	void traverse (){
			node *temp= head ; 
			cout << "\nTransitions : "<<endl << endl ; 
			output << "\nTransitions : "<<endl << endl ; 
			while (temp){
				cout << temp->from << " ---"<<temp->trans<<"---> "<<temp->to<<endl;
				output << temp->from << " ---"<<temp->trans<<"---> "<<temp->to<<endl;
				temp= temp->next;
			}
			cout << endl << endl ;
			output << endl << endl ;
			return;
		}
	int noOfStates (string from, char ch){
		node *temp = new node ;
		int counter = 0;
		while (temp){
			if (temp->from == from && temp->trans==ch){
				counter++;
			}
			temp= temp->next ;
		}
		return counter ; 
	}

	void copyelements (nfatransitions *temp){
			
			node *temp2=temp->head;
			while (temp2){
				this->insertion(temp2->from, temp2->to, temp2->trans);
				temp2=temp2->next;
			}
			return ; 
		}
};

class nodeLinkedlist {
	public : 
		string str;
		int num; 
		nodeLinkedlist *next ;
		nodeLinkedlist(){
			next=NULL;
		}
};

class linkedlist {
	nodeLinkedlist *head ; 
	public : 
		linkedlist (){
			head = NULL ; 
		}
		bool isEmpty (){
			if (head==NULL){
				return true;
			}
			return false ;
		}
		
		void clear (){
			head=NULL;

			return;
		}
		
		void insertion (string data ){	
			if (find(data))
			return;
			nodeLinkedlist *temp = new nodeLinkedlist ;
			temp->str= data ;
			if (head == NULL){
				temp->num = 0;
				temp->next = head;
				head = temp;
				return;
			}

			int cou=1;
			nodeLinkedlist *temp1= head;
			while (temp1->next){
				temp1=temp1->next;
				cou++;
			}
			temp->num=cou;
			temp1->next= temp;
			return; 
		}		
	
		void deleteelement (string st){
			if (head==NULL)return;
			if (find(st)==false)return ;
			nodeLinkedlist *temp = head ;
			if (st.compare(head->str)==0){
				head=head->next;
				delete temp;
				while (temp){
					temp->num--;
					temp=temp->next;
				}
				return;
			}
			temp=NULL;
			nodeLinkedlist *pri = head ; 
			nodeLinkedlist *current= head->next;
			while (current){
				if (st.compare(current->str)==0){
					temp=current;
					delete current;
					break;
				}else {
					pri =pri->next;
					current= current->next;
				}
				
			}
								
				if (temp!=NULL)pri->next= temp->next;
				nodeLinkedlist *t = head; 
				int n=0;
				while (t){
					t->num=n++;
					t=t->next;
				}
		}
		
		void traverse (){
			nodeLinkedlist *temp= head ; 
			while (temp){
				cout << temp->str<< " ";
				output << temp->str << " ";
				temp= temp->next;
			}
			return;
		}
		
		void traverse1 (){
			nodeLinkedlist *temp= head ; 
			while (temp){
				cout << temp->str;
				output << temp->str;
				temp= temp->next;
			}
			return;
		}
		
		bool find (string s){
			if (head==NULL)return false;
			nodeLinkedlist *tempnode = new nodeLinkedlist ; 
			tempnode=head;
			while (tempnode){
				if (s.compare(tempnode->str)==0){
				return true;
				}
				tempnode= tempnode->next;
			}
			return false;
		}
		
		int count (){
			int counter= 0;
			nodeLinkedlist *node = head; 
			while (node){
				counter++;
				node= node->next;
			}
			return counter;
		}
		
		string &getstate(int statenum){
			nodeLinkedlist *node = head ; 
			while (node){
				if (statenum==node->num){
					break ;
				}
				node= node->next;
			}
			return node->str;
		}
		void eClosure (string from, linkedlist *states, nfatransitions *temp1){

			this->clear();
			string to;
		    this->insertion(from);
			to=this->search(from, '@', states, temp1);
				for (int j=0; j<states->count(); j++){
                        to.clear();
						to=this->search(from, '@', states, temp1);
					if (states->find(to)){			
						from=to;
					}else {
						break;
					}
					}
				}
			
			
		void stateClosure (string from, char ch,  linkedlist *states, nfatransitions *temp1){

			node *temp = temp1->returnhead();
			while (temp){
				if (temp->from==from && temp->trans==ch){
					this->insertion(temp->to);
				}
				temp=temp->next;
			}
		}

			
			
		void generatingNfA (string from, string trans, linkedlist *states, nfatransitions *t){ 
			string str;
		    nodeLinkedlist *temp = new nodeLinkedlist ; 
			this->eClosure(from, states, t);

			linkedlist *abc = new linkedlist ;
			for (int i=0; i<this->count(); i++){
				abc->insertion(this->getstate(i));
			}
			for (int i=0 ; i<abc->count(); i++ ){
				from=abc->getstate(i);
				this->deleteelement(from);
				this->stateClosure(from, trans[0], states, t);
			}
			linkedlist *templ= new linkedlist ; 
			linkedlist *tempp = new linkedlist ;
				templ->copyelements(this);
				for (int i=0; i<templ->count();i++){
				tempp->eClosure(templ->getstate(i), states, t);
			    this->copyelements(tempp);
			}
		}
		
		void copyelements (linkedlist *temp){
			if (temp->isEmpty())return;
			nodeLinkedlist *temp2=temp->head;

			while (temp2){
				this->insertion(temp2->str);
				temp2=temp2->next;
			}
			return ; 
		}
		bool compareLL (linkedlist *A){
			if (head==NULL)return false;
			if (A->count()!= this->count())return false; 
			nodeLinkedlist *temp = head ;
			while (temp){
				if (!(A->find(temp->str)))return false;
				temp=temp->next ; 
			}
			return true;
		}
		
		string search(string state,char variable, linkedlist *l, nfatransitions *t){
		string st;
		st.clear();
		if (l->find(state)==false)return st;
		node *temp = t->returnhead(); 
		
		while (temp){
			if (temp->from==state && temp->trans==variable){
				if (l->find(temp->to)){
					st.clear();
				    st= temp->to;
					this->insertion(temp->to);
				}

			}
			temp=temp->next;
		}
		 return st ;
	}
	
};



bool areEqual (linkedlist *A, linkedlist *B){
	if (A->isEmpty() || B->isEmpty()){	
	return false;
	}
	if (A->compareLL(B) && B->compareLL(A)){
		return true;
	}
	return false ;
}


int main (){
	output.open("output.txt");
	cout << "E_NFA: "<<endl << endl ;
	output << "E_NFA: "<<endl << endl ;
	fstream ptr;
	
	int counter=0 ;
	int flag=1;
	int flag1=0;
	string temp;
	char ch, transition;
	string to, from ;
	
	linkedlist nfaStates;
	linkedlist initial;
	linkedlist final;
	linkedlist variables;
	
	nfatransitions t;
	
	ptr.open("input.txt");
	if (ptr.fail()){
		cout << endl << endl << "Input File doesn't exist !!"<<endl ;
		exit(0);
	}
	
	for (int i=1; i<=2; i++){		
		while (1){
		ptr.get(ch);
		if (ch!=','&&ch!=' '&&ch!='\n')
		temp.push_back(ch);
		if (ch==','||ch=='\n'){
			if (i==1)initial.insertion(temp);
			else
			final.insertion(temp);
			temp.clear();
		}
		if (ch=='\n')break;
		}
	
	}
	cout << "Initial States : ";
	output << "Initial States : ";
	initial.traverse();
	cout << "\n\nFinal States : ";
	output<< endl << endl << "Final States : ";
	final.traverse();

	
	while(!ptr.eof()){
		for (int i=0; i<2; i++){
			ptr>>temp;
			if (ptr.eof())break;
			if(i==0) from=temp;
			else to=temp;
			if (nfaStates.find(temp))
			{
				flag=0;
			}
			else
			flag=1;
			if (flag == 1){
			nfaStates.insertion(temp);
			}
		}
		if (ptr.eof())break;
		ptr >>temp ;
		if (temp!="@")
		variables.insertion(temp);
		else flag1=1;
		transition=temp[0];
		t.insertion(from,to,transition);

	}
	cout << "\n\nTotal States :";
	output << "\n\nTotal States :";
	nfaStates.traverse();
	cout << endl;
    output << endl;
	t.traverse();
	ptr.close();

linkedlist E_transitions[nfaStates.count()];


cout << endl << "E Closure Transions : "<<endl << endl ; 
output << endl << "E Closure Transions : "<<endl << endl ; 
for (int i=0; i<nfaStates.count(); i++){
	
	E_transitions[i].eClosure(nfaStates.getstate(i), &nfaStates, &t);
	cout << nfaStates.getstate(i)<<"-- @ --> "; 
	output << nfaStates.getstate(i)<<"-- @ --> "; 	
	E_transitions[i].traverse();
	cout << endl ; 
	output << endl;
}

	cout <<endl << endl << "transition Symbols : "; 
	output <<endl << endl << "transition Symbols : "; 
	variables.traverse();
	if (flag1==1){
	cout << "@"<< endl ;
	output << "@"<< endl ;
	}
	cout << endl << endl <<"NFA Transitions : "<<endl;
	output << endl << endl <<"NFA Transitions : "<<endl;	
		linkedlist abc;

	for (int i=0 ; i<nfaStates.count() ; i++){
		for (int j=0 ; j<variables.count() ; j++){
			abc.clear();
		cout << nfaStates.getstate(i)<<" --- "<<variables.getstate(j)<<" --> ";
		output << nfaStates.getstate(i)<<" --- "<<variables.getstate(j)<<" --> ";
		abc.generatingNfA(nfaStates.getstate(i), variables.getstate(j), &nfaStates, &t);
		if (abc.isEmpty()){
			cout << "Null";
			output << "Null";
		}else
		abc.traverse();
		cout << endl ;
		output << endl ;
		}
	}
	int n=1;
	for (int i=0;i<nfaStates.count();i++){
		n*=2;
	}
	linkedlist dfa[n];
	linkedlist *temporary = new linkedlist ;
	if (initial.count()>1){
		dfa[0].copyelements(&initial);
	}else if (initial.count()==1){
		dfa[0].copyelements(&initial);	
	}
	
	for (int i=0; i<dfa[0].count(); i++){
	temporary->eClosure(dfa[0].getstate(i), &nfaStates, &t);
	if (temporary->isEmpty())
	continue;
	dfa[0].copyelements(temporary);	
	}
	
	
	linkedlist abcde[variables.count()];
	int countt=0;
	cout << endl <<endl;
	output << endl << endl ;
	cout<<"\t\t_____________"<<endl<<"\t\t***  DFA  ***"<<endl<<"\t\t`````````````" << endl ; 
	output<<"\t\t_____________"<<endl<<"\t\t***  DFA  ***"<<endl<<"\t\t`````````````" << endl ; 	
	cout << "STATES\t\t "<<variables.getstate(0)<<"\t\t "<<variables.getstate(1)<< endl ;
	output << "STATES\t\t "<<variables.getstate(0)<<"\t\t "<<variables.getstate(1)<< endl ;	
	for (int i=0; i<n;i++){
		if (dfa[i].isEmpty())break;
        cout << endl ;
        output << endl;
		dfa[i].traverse1();
		abcde[0].clear();
		for (int j=0; j<dfa[i].count(); j++){
                temporary->generatingNfA(dfa[i].getstate(j), variables.getstate(0), &nfaStates, &t);
                abcde[0].copyelements(temporary);
                temporary->clear();
		}		
				cout << "  \t\t" ;
				output << "  \t\t" ;
				if (abcde[0].isEmpty()){
				cout << "Trap State";
				output << "Trap State";
				}
				else
				abcde[0].traverse1();
				flag=1;
				for (int k=0;k<=countt;k++){
					if (areEqual(&abcde[0], &dfa[k]))flag=0;
				}
				if (flag){
					if (!(abcde[0].isEmpty())){
					countt++;
					dfa[countt].copyelements(&abcde[0]);
					abcde[0].clear();
					}
				}
				abcde[1].clear();
		for (int j=0; j<dfa[i].count(); j++){

		    temporary->clear();
			temporary->generatingNfA(dfa[i].getstate(j), variables.getstate(1), &nfaStates, &t);
            abcde[1].copyelements(temporary);
            temporary->clear();		 

		}
				cout << "\t\t" ;
				output << "\t\t" ;
				if (abcde[1].isEmpty()){
				cout << "Trap State";
				output << "Trap State";
				}
				else
				abcde[1].traverse1();
				flag=1;
				for (int k=0;k<=countt ;k++){
					if (areEqual(&abcde[1], &dfa[k]))flag=0;
				}
				if (flag){
					if (!(abcde[1].isEmpty())){
					countt++;
					dfa[countt].copyelements(&abcde[1]);
					abcde[1].clear();
					}

				}
	}
	
	output<< endl << endl ;
	cout << endl << endl ;
	output << "*****************************************************"<< endl << endl ;
	cout << "*****************************************************"<< endl << endl ;
	output << "Initial State of DFA: ";
	cout << "Initial State Of DFA: ";
	dfa[0].traverse1();
	output << endl << endl ;
	cout <<endl << endl ; 	
	output << "Final States of DFA: ";
	cout << "Final States of DFA: ";
	for (int i=0; i<=countt; i++){
		for (int j=0; j<dfa[i].count(); j++){
			for (int k=0; k<final.count(); k++){
				if (final.getstate(k)==dfa[i].getstate(j)){
					dfa[i].traverse1();
					cout << " ";
					output << " ";
					j=dfa[i].count();
					k=final.count();
				}
			}
		}
	}
	
	output.close();

	cout <<endl << endl ; 	
	output << endl << endl ;
	return 0;	
}
