FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y apt-transport-https
RUN apt-get install -y apt-utils
RUN apt-get install -y xinetd
RUN apt-get install -y zbar-tools

RUN groupadd -r ctf && useradd -r -g ctf ctf
ADD ctf.xinetd /etc/xinetd.d/ctf
ADD ./files/ /home/ctf/

RUN chmod 440 /home/ctf/*
RUN chown -R root:ctf /home/ctf
RUN chmod 750 /home/ctf/redir.sh
RUN chmod 750 /home/ctf/qrona

RUN service xinetd restart
CMD ["/usr/sbin/xinetd", "-dontfork"]