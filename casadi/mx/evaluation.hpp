/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef EVALUATION_HPP
#define EVALUATION_HPP

#include "multiple_output.hpp"
#include "../fx/fx.hpp"

namespace CasADi{

/** 
  \author Joel Andersson 
  \date 2010-2011
*/
class Evaluation : public MultipleOutput{
  public:

    /** \brief  Constructor */
    explicit Evaluation(const FX& fcn, const std::vector<MX> &dep);
    
    /** \brief  Destructor */
    virtual ~Evaluation(){}
  
    /** \brief  Clone function */
    virtual Evaluation* clone() const;

    /** \brief  Print */
    virtual void print(std::ostream &stream, const std::vector<std::string>& args) const;

    /** \brief  Evaluate the function numerically */
    virtual void evaluate(const DMatrixPtrV& input, DMatrixPtrV& output, const DMatrixPtrVV& fwdSeed, DMatrixPtrVV& fwdSens, const DMatrixPtrVV& adjSeed, DMatrixPtrVV& adjSens);

    /** \brief  Evaluate the function symbolically (SX) */
    virtual void evaluateSX(const SXMatrixPtrV& input, SXMatrixPtrV& output, const SXMatrixPtrVV& fwdSeed, SXMatrixPtrVV& fwdSens, const SXMatrixPtrVV& adjSeed, SXMatrixPtrVV& adjSens);

    /** \brief  Evaluate the function symbolically (MX) */
    virtual void evaluateMX(const MXPtrV& input, MXPtrV& output, const MXPtrVV& fwdSeed, MXPtrVV& fwdSens, const MXPtrVV& adjSeed, MXPtrVV& adjSens, bool output_given);

    /** \brief  Check if evaluation */
    virtual bool isEvaluation() const{return true;}

    /** \brief  Get function reference */
    virtual FX& getFunction();

    /** \brief  Get function input */
    virtual int getFunctionInput() const{ return -1;}

    /** \brief  Get function output */
    virtual int getFunctionOutput() const{ return -1;}

    /** \brief  Deep copy data members */
    virtual void deepCopyMembers(std::map<SharedObjectNode*,SharedObject>& already_copied);

    /** \brief  Number of outputs */
    virtual int getNumOutputs() const{ return fcn_.getNumOutputs();}

    std::vector<SXMatrix> xs_;
    
    FX fcn_;
};

/** 
  \author Joel Andersson 
  \date 2010-2011
*/
class EvaluationOutput : public OutputNode{
  public:

    /** \brief  Constructor */
    explicit EvaluationOutput (const MX& parent, int oind);
  
    /** \brief  Destructor */
    virtual ~EvaluationOutput(){}

    /** \brief  Clone function */
    virtual EvaluationOutput * clone() const;

    /** \brief  Print */
    virtual void print(std::ostream &stream, const std::vector<std::string>& args) const;

    /** \brief  Get function reference */
    virtual FX& getFunction();
        
    /** \brief  Evaluate symbolically (SX) */
    virtual void evaluateSX(const std::vector<SXMatrix*> &input, SXMatrix& output);

};

} // namespace CasADi

#endif // EVALUATION_HPP
