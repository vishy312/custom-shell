FROM gcc:latest

WORKDIR /usr/local/app

COPY . .

RUN gcc -o custom-shell *.c

CMD [ "./custom-shell" ]