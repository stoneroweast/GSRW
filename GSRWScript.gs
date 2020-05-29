var SS = SpreadsheetApp.openById('1qzsgFov0xAfjVGOnN6NPAbl3JkClp9E3VJ1v7B6xy38');
var sheet = SS.getSheetByName('Sheet1');

function doGet(e){
  
  var cmd = e.parameter.cmd
  var cell = e.parameter.cell;
  var value = e.parameter.value;
  
  if (cmd != "read" && cmd != "write")
    return ContentService.createTextOutput("Undefined command");
  
  if (cell == undefined)
    return ContentService.createTextOutput("Undefined cell name ");
  
  if (value == undefined && cmd !="read")
    return ContentService.createTextOutput("Undefined cell value ");
  
  if (cmd == "write"){
    var range = sheet.getRange(cell);
    var retval = range.setValue(value).getValue();
    if (retval == e.parameter.value)
      return ContentService.createTextOutput("OK\r\n");
    else
      return ContentService.createTextOutput("Error\r\n");
  }
  else{
    return ContentService.createTextOutput(sheet.getRange(cell).getValue() + "\r\n");
  }
}
