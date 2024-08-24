FROM ubuntu:latest
WORKDIR /app
RUN apt update
COPY JoDServer .
CMD ["./JoDServer", "0.0.0.0", "8765"]
