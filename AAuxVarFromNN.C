#include <torch/script.h>                                   // add libtorch
#include "AAuxVarFromNN.h"

registerMooseObject("MooseApp", AAuxVarFromNN);               // register moose object

// define input parameters
InputParameters
AAuxVarFromNN::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredParam<FileName>("file_name", "name of the torchscript (neural network) file");
  params.addRequiredParam<Real>("Re", "Reynolds number");                                    
  //params.addRequiredCoupledVar("u", "velocity in x-direction");  
  return params;
}

// constructor
AAuxVarFromNN::AAuxVarFromNN(const InputParameters & parameters)
  : AuxKernel(parameters),
    _file_name(getParam<FileName>("file_name")),            // filename
    _Re(getParam<Real>("Re")) //,                        // maximum y coordinate
    //_grad_u(coupledGradient("u")) //,                          // velocity gradient
    //_mu(getMaterialProperty<Real>("dynamic_viscosity"))     // dynamic viscosity
{
    _inputs_tensor = torch::ones({1, 3}, at::kDouble);     // input tensor - move initialization here for efficiency
    _module = torch::jit::load(_file_name);                 // deserialize and load torchscript
}  

// compute function - pointwise prediction of turbulent viscosity
Real AAuxVarFromNN::computeValue()
{    
    //_y_w = 1.0 - std::abs(_q_point[_qp](1)) / _y_max;       // distance to the wall
    //_inputs_tensor[0][0] = std::abs(_grad_u[_qp](1));       // absolute velocity derivative
    //_inputs_tensor[0][1] = _y_w;                            // distance to the wall
    _inputs_tensor[0][0] = (_q_point[_qp](0) + 10.324234) / (15.0 + 10.324234);       // absolute velocity derivative
    _inputs_tensor[0][1] = (_q_point[_qp](1) - 0.0) / (10.7043495 - 0.0);                            // distance to the wall
    _inputs_tensor[0][2] = (_Re - 3000.0) / (14000.0 - 3000.0);
    std::vector<torch::jit::IValue> inputs{_inputs_tensor}; // cast to vector
    _outputs = _module.forward(inputs).toTensor().item<float>(); // get output
    
    //std::cout << "x=" << (_q_point[_qp](0) + 10.324234) / (15.0 + 10.324234) << "\n";
    //std::cout << "y=" << (_q_point[_qp](1) - 0.0) / (10.7043495 - 0.0) << "\n";
    //std::cout << "R=" << (_Re - 3000.0) / (14000.0 - 3000.0) << "\n";
    //std::cout << "O=" << _outputs*(0.0157798622 + 1.1355175e-05) - 1.1355175e-05 << "\n";
    
    return _outputs*(0.0157798622 + 1.1355175e-05) - 1.1355175e-05; //* _mu[_qp];                      // rescale
}