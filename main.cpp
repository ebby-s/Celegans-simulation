#include "network.hpp"
#include "frame.hpp"

using namespace std;

         // loads connections into a network object from a list of connections
             //expects format "presynaptic,postsynaptic,weight;"
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
  Network network(36);   // all neorons in network have threshold 36
  load_network(&network, cin);
      // stores names of all neurons in network
  const vector<string>* neuron_names = network.get_neuron_names();

  Frame frame(30, 20);      // states of neurons can be output using a pgm file
  vector<int> address(2,0);
  int total_cycles = atoi(argv[1]);  // command line argument determines total cycles to run for

  for(int i=0; i<total_cycles; i++){
    network.update();
    if(i==total_cycles-1){      // states of neurons written as pgm file after simulation
      for(int j=0; j<neuron_names->size(); j++){
        address[1] = j/30;
        address[0] = j%30;
        frame.set_pixel(address, (int)(!network.get_state((*neuron_names)[j])));
      }
      frame.to_pgm(40);     // scale factor 40 when pgm is created
      frame.clear();
    }
  }
}
