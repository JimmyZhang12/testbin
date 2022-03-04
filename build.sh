echo "*****SPMM*****"
rm -f tests/spmm
cd spmm
make clean && make
mv spmm ../tests
cd ..


echo "*****SPMM-REGULAR*****"
rm -f tests/spmm_regular
cd spmm_regular
make clean && make
mv spmm_regular ../tests
cd ..


echo "*****MATRIX MULT EIGEN*****"
rm -f tests/mm_eigen
cd mm_eigen
make clean && make
mv mm_eigen ../tests
cd ..


echo "*****HELLO WORLD*****"
rm -f tests/helloworld
cd helloworld
make clean && make
mv hw ../tests
cd ..

# echo "*****MATRIX MULT*****"
# rm tests/matrix_mult && rm tests/matrix_mult.fast
# cd matmul 
# make clean && make
# cp matrix_mult ../tests
# echo "*****MATRIX MULT O3*****"
# make clean
# make fast
# mv matrix_mult.fast ../tests
# cd ..



# echo "*****DFS GRAPH*****"
# # rm tests/graphs_dfs
# cd graph_dfs
# make fast
# mv graph_dfs.fast ../tests
# cd ..

