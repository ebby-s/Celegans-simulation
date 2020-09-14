#include "network.hpp"
#include "frame.hpp"

using namespace std;

void load_network(Network* network, istream &source){
  string input_line;
  vector<string> connection;
  int index = 0;
  while(source >> input_line){
    if(input_line.back()=='\n'){
      for(int i =0; i<input_line.size(); i++){
        if(input_line[i]==',' || input_line[i]=='\n'){
          index++;
          continue;
        }
        connection[index].append(input_line[i]);
      }
      network->add_synapse(connection[0], connection[1], stoi(connection[2]));
      input_line.erase();
      connection.clear();
    }
  }
}

int main(){
  Network network(40);
  load_network(&network, cin);
  vector<string>* neuron_names = network.get_neuron_names();

  Frame frame(30, 20);
  vector<int> address(2,0);

  for(int i=0; i<100; i++){
    network.update()
    for(int j=0; j<neuron_names->size(); j++){
      address[1] = j/30;
      address[0] = j%30;
      frame.set_pixel(address, (int)(!network.get_state(neuron_names[j])));
    }
    frame.to_pgm(40);
    frame.clear();
  }
}
