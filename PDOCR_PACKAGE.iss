; �ű��� Inno Setup �ű��� ���ɡ�
; �����ĵ���ȡ���� INNO SETUP �ű��ļ�����ϸ���ϣ�

#define MyAppName "PDOCR"
#define MyAppVersion "1.1"
#define MyAppPublisher "������progdomain.com"
#define MyAppURL "http://www.progdomain.com/"
#define MyAppExeName "PDOCR.exe"

[Setup]
; ע��: AppId ��ֵ��Ψһʶ���������ı�־��
; ��Ҫ������������ʹ����ͬ�� AppId ֵ��
; (�ڱ������е���˵������� -> ���� GUID�����Բ���һ���µ� GUID)
AppId={{29B0E385-32FE-49B3-BCD2-0735B4976867}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=.\
OutputBaseFilename=PDOCR
SetupIconFile=.\PDOCR\RES\PDOCR.ico
Compression=lzma
SolidCompression=yes
DisableWelcomePage=no
AppCopyright=Copyright(C)2023 ������.
PrivilegesRequired=admin
ArchitecturesInstallIn64BitMode=x64 ia64

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: checkablealone

[Files]
Source: "..\PDOCR\x64\Release\PDOCR.exe"; DestDir: "{app}"; Flags: ignoreversion; Permissions: everyone-modify
Source: "..\PDOCR\x64\Release\ch_PP-OCRv3_det_slim_infer\*"; DestDir: "{app}\ch_PP-OCRv3_det_slim_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\ch_PP-OCRv3_rec_slim_infer\*"; DestDir: "{app}\ch_PP-OCRv3_rec_slim_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\arabic_PP-OCRv3_rec_infer\*"; DestDir: "{app}\arabic_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\chinese_cht_PP-OCRv3_rec_infer\*"; DestDir: "{app}\chinese_cht_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\cyrillic_PP-OCRv3_rec_infer\*"; DestDir: "{app}\cyrillic_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\devanagari_PP-OCRv3_rec_infer\*"; DestDir: "{app}\devanagari_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\japan_PP-OCRv3_rec_infer\*"; DestDir: "{app}\japan_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\ka_PP-OCRv3_rec_infer\*"; DestDir: "{app}\ka_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\korean_PP-OCRv3_rec_infer\*"; DestDir: "{app}\korean_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\latin_PP-OCRv3_rec_infer\*"; DestDir: "{app}\latin_PP-OCRv3_rec_infer\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\dict\*"; DestDir: "{app}\dict\"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\PDOCR\x64\Release\BCGCBPRO3100u141.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\libiomp5md.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\mkldnn.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\mklml.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\onnxruntime.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\opencv_world470.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\paddle_inference.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\paddle2onnx.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\PDOCR\x64\Release\PDOCR.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\VC_redist.x64.exe"; DestDir: "{app}"; Flags: ignoreversion
; ע��: ��Ҫ���κι����ϵͳ�ļ�ʹ�� "Flags: ignoreversion"

[Dirs]
Name:{app}; Permissions: users-full

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
[Run]   
Filename: "{app}\VC_redist.x64.exe"; Parameters: /q; WorkingDir: {tmp}; StatusMsg: "Installing Microsoft Visual C++ Runtime ...";
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
