# MFC - File Date Read
MFC를 사용하여 파일의 만든 날짜, 수정한 날짜, 액세스한 날짜를 표시한다.

- CFileDialog를 DoModal하여 파일의 절대경로를 가져온다.

- 날짜는 DateTimePicker 도구로 DateTimeCtrl를 인스턴스화하여 년월일과 시분초를 나누어 표시했다.