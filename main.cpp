#include "network.hpp"
#include "frame.hpp"

using namespace std;

void load_network(Network* network, istream &source){
  char input_char;
  string input_line;
  vector<string> connection(3,"");
  int index = 0;

  while(source >> input_char){
    input_line.push_back(input_char);
    if(input_line.back()==';'){
      for(int i =0; i<input_line.size(); i++){
        if(input_line[i]==',' || input_line[i]==';'){
          index++;
          continue;
        }
        connection[index].push_back(input_line[i]);
      }
      network->add_synapse(connection[0], connection[1], stoi(connection[2]));
      input_line.erase();
      connection.assign(3,"");
      index = 0;
    }
  }
}

int main(int argc, char** argv){
  Network network(36);
  load_network(&network, cin);
  const vector<string>* neuron_names = network.get_neuron_names();

  Frame frame(30, 20);
  vector<int> address(2,0);
  int total_cycles = atoi(argv[1]);

  for(int i=0; i<total_cycles+1; i++){
    if(i<8){
      network.set_state("ASJL", true);
      network.set_state("ASJR", true);
      network.set_state("ASKL", true);
      network.set_state("ASKR", true);
      network.set_state("ASGL", true);
      network.set_state("ASGR", true);
      network.set_state("ASIL", true);
      network.set_state("ASIR", true);
    }
    network.update();
    if(i==total_cycles){
      for(int j=0; j<neuron_names->size(); j++){
        address[1] = j/30;
        address[0] = j%30;
        frame.set_pixel(address, (int)(!network.get_state((*neuron_names)[j])));
      }
      frame.to_pgm(40);
      frame.clear();
    }
  }
}
