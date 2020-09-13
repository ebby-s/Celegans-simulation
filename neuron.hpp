#include<vector>
#include<string>
#include<cassert>

class Neuron{
private:
  int threshold;
  bool state;
  bool next_state;
  vector<Neuron*> inputs;
  vector<int> weights;
public:
  Neuron(int new_threshold, vector<Neuron*> new_inputs, vector<int> weights){
    threshold = new_threshold;
    state = false;
    next_state = false;
    inputs = new_inputs;
    weights = new_weights;
    assert(inputs.size() == weights.size());
  }
  bool get_state(){
    return state;
  }
  bool get_next_state(){
    return next_state;
  }
  void set_state(bool new_state){
    state = new_state;
  }
  void set_next_state(bool new_next_state){
    next_state = new_next_state;
  }

  void step_time(){
    int weighted_input = 0;
    for(int i=0; i<inputs.size(); i++){
      weighted_input += (int)(inputs[i]->get_state()) * weights[i];
    }
    if(weighted_input > threshold){
      next_State = true;
    }
  }

  void update_state(){
    state = next_state;
    next_state = false;
  }
};
