echo "*****MATRIX MULT*****"
rm tests/matrix_mult && rm tests/matrix_mult.fast
cd matmul 
make clean && make
cp matrix_mult ../tests
echo "*****MATRIX MULT O3*****"
make clean
make fast
cp matrix_mult.fast ../tests
cd ..

echo "*****MATRIX MULT EIGEN*****"
rm tests/mm_eigen
cd mm_eigen
make clean && make
mv mm_eigen ../tests
cd ..