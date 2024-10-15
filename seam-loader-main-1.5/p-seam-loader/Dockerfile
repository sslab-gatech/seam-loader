FROM debian:buster

ARG project

RUN apt update \
 && apt install -y gnupg libssl-dev software-properties-common wget cmake nasm python3 bear && \
    ln -s /usr/bin/python3.7 /usr/bin/python

RUN echo "deb http://apt.llvm.org/buster/ llvm-toolchain-buster main" >> /etc/apt/sources.list && \
    echo "deb-src http://apt.llvm.org/buster/ llvm-toolchain-buster main" >> /etc/apt/sources.list && \
    echo "deb http://apt.llvm.org/buster/ llvm-toolchain-buster-10 main" >> /etc/apt/sources.list && \
    echo "deb-src http://apt.llvm.org/buster/ llvm-toolchain-buster-10 main" >> /etc/apt/sources.list && \
    echo "deb http://apt.llvm.org/buster/ llvm-toolchain-buster-11 main" >> /etc/apt/sources.list && \
    echo "deb-src http://apt.llvm.org/buster/ llvm-toolchain-buster-11 main" >> /etc/apt/sources.list

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
    apt update && \
    apt install -y clang-10

RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-10 1 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-10 1

WORKDIR $project

CMD ["bash", "-c", \
     "cd libs/ipp/ipp-crypto-ippcp_2021.4 && \
      CC=clang CXX=clang++ cmake CMakeLists.txt -B_build -DARCH=intel64 -DMERGED_BLD:BOOL=off -DPLATFORM_LIST=y8 && \
      cd _build && \
      make ippcp_s_y8 -j && \
      cd ../../../../ && \
      bear make DEBUGFEATURE_TDX_DBG_TRACE=1 -j"]
