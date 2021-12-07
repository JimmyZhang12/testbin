echo "*****MATRIX MULT*****"
rm tests/matrix_mult && rm tests/matrix_mult.fast
cd matmul 
make clean && make
cp matrix_mult ../tests
echo "*****MATRIX MULT O3*****"
make clean
make fast
mv matrix_mult.fast ../tests
cd ..

echo "*****MATRIX MULT EIGEN*****"
rm tests/mm_eigen
cd mm_eigen
make clean && make
mv mm_eigen ../tests
cd ..


echo "*****DFS GRAPH*****"
# rm tests/graphs_dfs
cd graph_dfs
make clean && make fast
mv graph_dfs.fast ../tests
cd ..