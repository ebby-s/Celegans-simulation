g++ main.cpp -o simulator

for i in {0..10}
do
  ./simulator $i < male_connections.txt > result/$i.pgm
done
