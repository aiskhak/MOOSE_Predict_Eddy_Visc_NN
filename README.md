# MOOSE_Predict_Eddy_Visc_NN
Finite Volume NS MOOSE kernel that reads a torchscript NN model to predict eddy viscosity

Please cite our work if this is helpful:

Data-driven Hi2Lo for Coarse-grid System Thermal Hydraulic Modeling
Arsen S. Iskhakov, Nam T. Dinh, Victor Coppo Leite, Elia Merzari
2022
https://doi.org/10.48550/arXiv.2203.03577

Compilation is highly dependent on the environment. In my case the following steps apply (RDFMG cluster):

1. set up moose environment as https://mooseframework.inl.gov/getting_started/installation/conda.html
2. conda install -c brown-data-science numactl	# if numa error is thrown; DO THIS BEFORE CONFIGURING MOOSE ENVIRONMENT!!!
4. git clone -b master --recurse-submodule https://github.com/pytorch/pytorch.git
5. mkdir pytorch-build-moose
6. cd pytorch-build-moose
7. pip install typing_extensions
8. cmake -DUSE_CUDA=OFF -DUSE_CUDNN=OFF -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_BUILD_TYPE:STRING=Release -DPYTHON_EXECUTABLE:PATH=`which python3` -DCMAKE_INSTALL_PREFIX:PATH=../pytorch-install-moose ../pytorch
9. module load numactl/2.0.12-GCCcore-8.3.0  #RDFMG#
10. cmake --build . --target install -- -j 16

# do this only before compiling app (not when running)
module load numactl/2.0.12-GCCcore-8.3.0
module load OpenBLAS/0.3.7-GCC-8.3.0

Notes: make sure your environment is not contaminated (if using mamba, remove and clean anaconda, etc.)

# unload modules before submitting a job
module unload numactl/2.0.12-GCCcore-8.3.0
module unload OpenBLAS/0.3.7-GCC-8.3.0

module load openblas/dynamic/0.3.7
 
# remove -D_GLIBCXX_USE_CXX11_ABI=0 -std=c++11 from the Makefile of SAM!
### ATTENTION: 
### maybe needed. DO THIS BEFORE CONFIGURING MOOSE ENVIRNMENT!!!!
git clone -b master --recurse-submodule https://github.com/pytorch/pytorch.git      # some errors with vfloat2 type 

git clone -b lts/release/1.8 --recurse-submodule https://github.com/pytorch/pytorch.git  # maybe older version 

mkdir pytorch-build
cd pytorch-build
pip install typing_extensions
cmake -DUSE_CUDA=OFF -DUSE_CUDNN=OFF -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_BUILD_TYPE:STRING=Release -DPYTHON_EXECUTABLE:PATH=`which python3` -DCMAKE_INSTALL_PREFIX:PATH=../pytorch-install ../pytorch
#module load numactl/2.0.12-GCCcore-8.3.0  #RDFMG#
cmake --build . --target install -- -j 7
