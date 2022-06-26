FROM registry.playteam.ru/debian:stable-20210816-217 as build

ARG PROXY_HOST
ARG NO_PROXY
ENV HTTP_PROXY $PROXY_HOST
ENV HTTPS_PROXY $PROXY_HOST
ENV NO_PROXY $NO_PROXY
ENV http_proxy $PROXY_HOST
ENV https_proxy $PROXY_HOST
ENV no_proxy $NO_PROXY

RUN apt-get update &&\
    apt-get install -y build-essential &&\
    apt-get install -y git &&\
    apt-get install -y gdb make ninja-build rsync zip &&\
    apt-get install -y cmake &&\
    apt-get install -y curl unzip &&\
    apt-get install -y clang &&\
    apt-get install -y libcurl4-openssl-dev &&\
    apt-get install -y libssl-dev


RUN apt update

RUN apt-get update && apt-get clean all

RUN apt-get install -y openssh-server

RUN mkdir /var/run/sshd

RUN echo 'root:pass' | chpasswd

RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

 

# SSH login fix. Otherwise user is kicked off after login

RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

RUN /usr/bin/ssh-keygen -A

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]
