FROM ubuntu:latest
WORKDIR /app
RUN apt update
RUN apt install -y libpq-dev
COPY JoDServer .
CMD ["./JoDServer", "0.0.0.0", "8765"]
