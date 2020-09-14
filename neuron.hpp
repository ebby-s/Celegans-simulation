#include<vector>
#include<string>
#include<cassert>

using namespace std;

class Neuron{
private:
  int threshold;     // threshold for neuron to fire
  bool state;             // is neuron currently firing
  bool next_state;               // is neuron going to fire this cycle
  vector<Neuron*> inputs;     // all presynaptic neurons
  vector<int> weights;    // weight of each connection, in same order as inputs
public:
  Neuron(int new_threshold){
    threshold = new_threshold;
    state = false;
    next_state = false;
  }

  bool get_neuron_state() const{
    return state;
  }
  void set_neuron_state(bool new_state){
    state = new_state;
  }

  void add_connection(Neuron* new_input, int new_weight){
    inputs.push_back(new_input);
    weights.push_back(new_weight);
  }

  void step_time(){        // calculate whether neuron will fire next cycle
    int weighted_input = 0;
    for(int i=0; i<inputs.size(); i++){
      weighted_input += (int)(inputs[i]->get_neuron_state()) * weights[i];
    }
    if(weighted_input > threshold){
      next_state = true;   // if threshold reached, neuron will fire next cycle
    }
  }

  void update_state(){
    state = next_state;
    next_state = false;
  }
};
