#include<map>
#include<iostream>
#include "neuron.hpp"

using namespace std;

class Network{
private:
  int threshold;         // all neurons in network share the same threshold
  map<string,Neuron*> neurons_by_name;  //map of names to neurons
  vector<string> neuron_names;  // list of names of all the neurons in the network
public:
  Network(int new_threshold){
    threshold = new_threshold;
  }
  bool get_state(string name){      // get the state of a neuron
    return neurons_by_name[name]->get_neuron_state();
  }
  const vector<string>* get_neuron_names() const{   // get list of all names
    return &neuron_names;
  }
  void set_state(string name, bool new_state){    // set state of a neuron
    neurons_by_name[name]->set_neuron_state(new_state);
  }
         // adds a synapse, creates neurons if not already present
  void add_synapse(string presynaptic, string postsynaptic, int weight){
    if(neurons_by_name.count(presynaptic) == 0){
      Neuron* new_pre = new Neuron(threshold);
      neurons_by_name.insert(pair<string,Neuron*> (presynaptic, new_pre));
      neuron_names.push_back(presynaptic);
    }
    if(neurons_by_name.count(postsynaptic) == 0){
      Neuron* new_post = new Neuron(threshold);
      neurons_by_name.insert(pair<string,Neuron*> (postsynaptic, new_post));
      neuron_names.push_back(postsynaptic);
    }

    neurons_by_name[postsynaptic]->add_connection(neurons_by_name[presynaptic], weight);
  }

  void update(){     // updates all neurons in the network
    for(int i=0; i<neuron_names.size(); i++){
      neurons_by_name[neuron_names[i]]->step_time();
    }
    for(int i=0; i<neuron_names.size(); i++){
      neurons_by_name[neuron_names[i]]->update_state();
    }
  }
};
