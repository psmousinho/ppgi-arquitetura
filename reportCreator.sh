#!/bin/bash

nImage=$1
echo "Removendo relatórios antigos"
rm relatorios/mainwrong/$nImage 
rm relatorios/mainrightloop/$nImage
rm relatorios/mainloopfusion/$nImage
rm relatorios/mainrightloopfusion/$nImage
rm relatorios/mainrightloopfusionparallel/$nImage 
rm relatorios/reportAnalyzer/$nImage

echo "Criando relatórios para " $nImage " imagens"
echo "Executando o Main-Wrong"
for i in {1..10}; do ./Main-Wrong $nImage; done
echo "##############################################"
echo "Executando o Main-RightLoop"
for i in {1..10}; do ./Main-RightLoop $nImage; done
echo "##############################################"
echo "Executando o Main-LoopFusion"
for i in {1..10}; do ./Main-LoopFusion $nImage; done
echo "##############################################"
echo "Executando o Main-RightLoopFusion"
for i in {1..10}; do ./Main-RightLoopFusion $nImage; done
echo "##############################################"###
echo "Executando o Main-RightLoopFusionParallel"
for i in {1..10}; do ./Main-RightLoopFusionParallel $nImage 2; done
echo "##############################################"

echo "Analisando relatórios"
./reportAnalyzer "relatorios/mainwrong/" $nImage
./reportAnalyzer "relatorios/mainloopfusion/" $nImage
./reportAnalyzer "relatorios/mainrightloop/" $nImage
./reportAnalyzer "relatorios/mainrightloopfusion/" $nImage 
./reportAnalyzer "relatorios/mainrightloopfusionparallel/" $nImage
