Steps to create the service:
1) take the logger.service file provided in systemd_service_file
2) put it inside the etc/systemd/system 
3) sudo systemctl daemon-reload
4) sudo systemctl enable logger.service
5) sudo systemctl start logger.service