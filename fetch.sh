#!/bin/bash
datasets=("samuelcortinhas/2d-clustering-data" "joonasyoon/clustering-exercises" )
target_dir="./dataset"
for dataset in "${datasets[@]}"; do
    if [ ! -e ${target_dir} ]; then
        mkdir ${target_dir} 
    fi
    cd ${target_dir}
    kaggle datasets download -d "${dataset}" --unzip
done
