#!/usr/bin/bash


docker image inspect p-seam-loader >/dev/null || {
    docker build --build-arg project=$PWD -t p-seam-loader:latest .
}

[ -d libs/ipp/ipp-crypto-ippcp_2021.4 ] || {
    git clone -b ippcp_2021.4 --depth=1 https://github.com/intel/ipp-crypto libs/ipp/ipp-crypto-ippcp_2021.4
}

docker run --rm -v $PWD:$PWD --name p-seam-loader p-seam-loader
