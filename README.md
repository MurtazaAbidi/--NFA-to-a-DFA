# --NFA-to-a-DFA

Algorithm converting an ε-NFA to a DFA Using C++

1- An Input file consist of ε-NFA such that : 

-> First Line consist of initial states(if more than one then separate them by comma without any space (ie. q0,q1,q2) ) of ε-NFA,

-> Second line consist of Final States((if more than one then separate them by comma without any space (ie. q0,q1,q2) ) of ε-NFA, 

-> And remaining lines consist of the all the transitions of ε-NFA such that:
q0 q1 a (From: q0 , to: q1 , transtion variable : a)
for NULL transitions use @ symbol

2) First we convert an ε-NFA to NFA, by terminating all the null transitions.

3) Now, NFA is converted into DFA.

4) An Output file is created, which consist of, 

->Transions of ε-NFA.

-> ε-Closure Transitions.

-> NFA transitions.

-> And DFA Transitions.

-> If there is no transition for a transition-symbol from any state, then that transition is forming a trap state in that DFA.

5) So, this is how we converted a ε-NFA to DFA using C++.
