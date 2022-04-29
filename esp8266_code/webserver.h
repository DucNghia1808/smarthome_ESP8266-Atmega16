//=========File chứa mã HTLM Website==//
const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <meta charset="UTF-8">
    <head>
        <title>nhacuanghia</title>
        <style>
            body{
                text-align: center;
            }
            #hide{
                margin:10px;
                padding: 25px;
                color: white;
                display: none;
            }
            #login{
                width: 300px;
                height: 280px;
                border: 3px solid grey;
                border-radius: 15px;
                text-align: center;
                margin: 0 auto;
            }
            #login h5{
                color:#1b2020;
                font-family: sans-serif;
            }
            #login input{
                width: 170px;
                height: 35px;
                margin-bottom: 10px;
                border-radius: 7px;
                border: 1px solid grey;
                padding-left: 20px;
            }
            #login button{
                width:100px;
                height: 40px;
                margin-bottom: 10px;
                border-radius: 12px;
                background-color: rgb(40, 119, 129);
                color: white;
            }
            button:hover{
                font-size: 14px;
            }
            .switch {
            position: relative;
            display: inline-block;
            width: 50px;
            height: 23px;
            }

            .switch input { 
                opacity: 0;
                width: 0;
                height: 0;
            }
            .slider {
                position: absolute;
                cursor: pointer;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
                background-color: #ccc;
                -webkit-transition: .4s;
                transition: .4s;
            }
            .slider:before {
                position: absolute;
                content: "";
                height: 16px;
                width: 16px;
                left: 4px;
                bottom: 4px;
                background-color: white;
                -webkit-transition: .4s;
                transition: .4s;
            }
            input:checked + .slider {
                background-color: #2196F3;
            }
            input:focus + .slider {
                box-shadow: 0 0 1px #2196F3;
            }
            input:checked + .slider:before {
                -webkit-transform: translateX(26px);
                -ms-transform: translateX(26px);
                transform: translateX(26px);
            }
                /* Rounded sliders */
            .slider.round {
                border-radius: 34px;
            }
            .slider.round:before {
                border-radius: 50%;
            }
            button{
                width:80px;
                height: 30px;
                border-radius: 7px;
            }
            table{
                text-align: center;
                margin: 0 auto;
                background: rgb(32, 138, 138);
                height: 75%;
                width: 500px;
                height:200px;
            }
            tr{
                height: 50px;              
            }
        </style>
    </head>
<body  onload="UpdateData()">
    <div id="login">
        <h2> MY HOME </h2>
        <h5>Tài khoản
            <input type=" text" placeholder="username" id="Username">
        </h5>
        <h5>Mật khẩu
            <input type="password" placeholder="password" id="Password">
        </h5>
        <button id="myBtn" onclick="check_input()">Đăng Nhập</button>
    </div>
    <div id="hide">
        <table border="2" >
            <tr style=" height:100px;">
              <td colspan="4" >ESP8266 WEBSERVER</td>
            </tr>
          <tr><!-- hàng  1-->            
              <td>THIẾT BỊ</td> <!-- cột 1-->
              <td colspan="3" >TRẠNG THÁI</td>
          </tr>
          <tr>
              <td>ĐÈN KHÁCH</td>
              <td>
                  <label class="switch" id="switch1" onclick="GetButtonData(1)">
                  <input id="inputSwitch1" type="checkbox" >
                  <span class="slider round"></span>
                  </label>
              </td>
              <td><label id="tttb1">OFF</label></td>
              <td rowspan="2">
                  Nhiệt Độ
                  <br> 
                  <label id="nhietdo">0</label>
                  <label >  &#176;C</label>
              </td>
          </tr>
          <tr>
            <td>ĐÈN BẾP</td>
            <td>
                <label class="switch" id="switch2" onclick="GetButtonData(2)">
                  <input id="inputSwitch2" type="checkbox" >
                  <span class="slider round"></span>
                </label>
            </td>
            <td><label id="tttb2">OFF</label></td>
          </tr>
          <tr>
              <td>ĐÈN NGỦ 1</td>
              <td>
                  <label class="switch" id="switch3" onclick="GetButtonData(3)">
                    <input id="inputSwitch3" type="checkbox" >
                    <span class="slider round"></span>
                  </label>
              </td>
              <td><label id="tttb3">OFF</label></td>
              <td rowspan="2">
                Độ Ẩm
                <br> 
                <label id="doam">0</label>
                <label > %</label>
            </td>
          </tr>
          <tr>
              <td>ĐÈN NGỦ 2</td>
              <td>
                  <label class="switch" id="switch4" onclick="GetButtonData(4)">
                    <input id="inputSwitch4" type="checkbox" >
                    <span class="slider round"></span>
                  </label>
              </td>
              <td><label id="tttb4">OFF</label></td>
            </tr>
        <tr>
            <td>QUẠT BẾP</td>
            <td>
                <label class="switch" id="switch5" onclick="GetButtonData(5)">
                    <input id="inputSwitch5" type="checkbox" >
                    <span class="slider round"></span>
                </label>
            </td>
            <td><label id="tttb5">OFF</label></td>
        </tr>
        <tr>
            <td>QUẠT KHÁCH</td>
            <td>
                <label class="switch" id="switch6" onclick="GetButtonData(6)">
                    <input id="inputSwitch6" type="checkbox" >
                    <span class="slider round"></span>
                </label>
            </td>
            <td><label id="tttb6">OFF</label></td>
        </tr>
        
        <tr>
            <td>CỬA BẾP</td>
            <td>
                <label class="switch" id="switch7" onclick="GetButtonData(7)">
                  <input id="inputSwitch7" type="checkbox" >
                  <span class="slider round"></span>
                </label>
            </td>
            <td><label id="tttb7">OFF</label></td>
        </tr>
        <tr>
            <td>PHƠI ĐỒ</td>
            <td>
                <label class="switch" id="switch8" onclick="GetButtonData(8)">
                    <input id="inputSwitch8" type="checkbox" >
                    <span class="slider round"></span>
                </label>
            </td>
            <td><label id="tttb8">OFF</label></td>
        </tr>
          <tr>
              <td colspan="3">
                  <button id="reload" onclick="lockpage()">Thoát</button>
              </td>
          </tr>
      </table>
    </div>
    <script>
        function lockpage(){
            document.getElementById("login").style.display="block";
            document.getElementById("hide").style.display="none";
            document.getElementById("Username").value='';
            document.getElementById("Password").value='';
        }
        var dataON=!document.getElementById("inputSwitch1").checked;// trạng thái nút nhấn
        var dataOFF=document.getElementById("inputSwitch1").checked;

        function UpdateData(){// nhận dữ liệu ESP gửi về
            var xhttp= new XMLHttpRequest();
            xhttp.onreadystatechange=function(){ //Một Event Handler lắng nghe và xử lý một sự kiện khi có thay đổi về trạng thái nào diễn ra.
                if(this.readyState==4&&this.status==200){
                    var DataVDK=xhttp.responseText;// giá trị nhân về
                    console.log("Dữ liệu VDK:"+DataVDK);// console.log hiển thị ra ------F12 để coi
                    var DataJson=JSON.parse(DataVDK);// lấy giá trị data JSON
                    
                    if(DataJson.ND!=null){
                        document.getElementById("nhietdo").innerHTML=DataJson.ND;
                    }/// lấy giá trị nhiệt độ JSON từ VĐK gán váo ô có id NHIỆT ĐỘ
                    if(DataJson.DA!=null){
                        document.getElementById("doam").innerHTML=DataJson.DA;
                    }/// lấy giá trị độ ẩm JSON từ VĐK gán váo ô có id ĐỘ ẨM

                    if(DataJson.TB1!=null){
                        if(DataJson.TB1==1){      // kiểm tra trạng thái thiết bị 1
                            document.getElementById("tttb1").innerHTML="ON";
                            document.getElementById("inputSwitch1").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb1").innerHTML="OFF";
                            document.getElementById("inputSwitch1").checked=dataOFF;                           
                        }

                    }
                    if(DataJson.TB2!=null){
                        if(DataJson.TB2==1){      // kiểm tra trạng thái thiết bị 2
                            document.getElementById("tttb2").innerHTML="ON";
                            document.getElementById("inputSwitch2").checked=dataON;                           

                        }
                        else{
                            document.getElementById("tttb2").innerHTML="OFF";
                            document.getElementById("inputSwitch2").checked=dataOFF;                           
                        }
                    }
                    if(DataJson.TB3!=null){
                        if(DataJson.TB3==1){      // kiểm tra trạng thái thiết bị 3
                            document.getElementById("tttb3").innerHTML="ON";
                            document.getElementById("inputSwitch3").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb3").innerHTML="OFF";
                            document.getElementById("inputSwitch3").checked=dataOFF;                           
                        }
                    }
                    if(DataJson.TB4!=null){
                        if(DataJson.TB4==1){      // kiểm tra trạng thái thiết bị 4
                            document.getElementById("tttb4").innerHTML="ON";
                            document.getElementById("inputSwitch4").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb4").innerHTML="OFF";
                            document.getElementById("inputSwitch4").checked=dataOFF;                           
                        }                       
                    }
                    if(DataJson.TB5!=null){
                        if(DataJson.TB5==1){      // kiểm tra trạng thái thiết bị 5
                            document.getElementById("tttb5").innerHTML="ON";
                            document.getElementById("inputSwitch5").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb5").innerHTML="OFF";
                            document.getElementById("inputSwitch5").checked=dataOFF;                           
                        }                       
                    }
                    if(DataJson.TB6!=null){
                        if(DataJson.TB6==1){      // kiểm tra trạng thái thiết bị 6
                            document.getElementById("tttb6").innerHTML="ON";
                            document.getElementById("inputSwitch6").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb6").innerHTML="OFF";
                            document.getElementById("inputSwitch6").checked=dataOFF;                           
                        }                       
                    }
                    if(DataJson.TB7!=null){
                        if(DataJson.TB7==1){      // kiểm tra trạng thái thiết bị 7
                            document.getElementById("tttb7").innerHTML="ON";
                            document.getElementById("inputSwitch7").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb7").innerHTML="OFF";
                            document.getElementById("inputSwitch7").checked=dataOFF;                           
                        }                       
                    }
                    if(DataJson.TB8!=null){
                        if(DataJson.TB8==1){      // kiểm tra trạng thái thiết bị 8
                            document.getElementById("tttb8").innerHTML="ON";
                            document.getElementById("inputSwitch8").checked=dataON;                           
                        }
                        else{
                            document.getElementById("tttb8").innerHTML="OFF";
                            document.getElementById("inputSwitch8").checked=dataOFF;                           
                        }                       
                    }
                }      
            }
            xhttp.open('GET','/Update',true);
            xhttp.send(); // gửi về địa chỉ 192.168.1.120/Update thay đổi đường dẫn
            setTimeout(function(){UpdateData()},1000);
        }// set time out cài đặt sau 1 giây update data1 lần
        var correct_User="admin";
        var correct_Pass="nghia";
        function GetButtonData(data){ // button được nhấn từ SERVER
            switch (data){
                case 1: // button 1 được nhấn từ SERVER
                    var thietbi1=document.getElementById("tttb1").innerHTML;
                    if(thietbi1=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="A0B";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi1=="OFF"){// còn lại nếu đang off bật lên
                        var tx="A1B";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;
                case 2: // button 2 được nhấn từ SERVER

                    var thietbi2=document.getElementById("tttb2").innerHTML;
                    if(thietbi2=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="C0D";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi2=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="C1D";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;     
                case 3: // button 3 được nhấn từ SERVER

                    var thietbi3=document.getElementById("tttb3").innerHTML;
                    if(thietbi3=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="E0F";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi3=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="E1F";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;           
                case 4: // button 4 được nhấn từ SERVER

                    var thietbi4=document.getElementById("tttb4").innerHTML;
                    if(thietbi4=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="G0H";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi4=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="G1H";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;
                case 5: // button 5 được nhấn từ SERVER

                    var thietbi5=document.getElementById("tttb5").innerHTML;
                    if(thietbi5=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="I0J";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi5=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="I1J";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;  
                case 6: // button 6 được nhấn từ SERVER

                    var thietbi6=document.getElementById("tttb6").innerHTML;
                    if(thietbi6=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="K0L";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi6=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="K1L";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;
                case 7: // button 7 được nhấn từ SERVER

                    var thietbi7=document.getElementById("tttb7").innerHTML;
                    if(thietbi7=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="M0N";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi7=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="M1N";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;  
                case 8: // button 8 được nhấn từ SERVER

                    var thietbi8=document.getElementById("tttb8").innerHTML;
                    if(thietbi8=="ON"){ // kiểm tra nếu đang ON gửi để tắt đi
                        var tx="O0P";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    else if(thietbi8=="OFF"){ // còn lại nếu đang off bật lên
                        var tx="O1P";
                        var xhttp=new XMLHttpRequest();
                        xhttp.open("GET","/Button?Button="+tx,true);
                        xhttp.send();
                    }
                    break;    
            }
        }
        
        var input = document.getElementById("Password"); // nhấn phím enter
        input.addEventListener("keyup", function(event) {
            if (event.keyCode === 13) {
                //event.preventDefault();
                document.getElementById("myBtn").click();
            }
        });
        var input = document.getElementById("Username"); // nhấn phím enter
        input.addEventListener("keyup", function(event) {
            if (event.keyCode === 13) {
               // event.preventDefault();
                document.getElementById("myBtn").click();
            }
        });
    
        function check_input(){
            var inputUsername=document.getElementById("Username").value;
            var inputPassword=document.getElementById("Password").value;
            
            if(inputUsername==correct_User&&inputPassword==correct_Pass){
                alert('Đăng nhập thành công'); 
                document.getElementById("hide").style.display="block";
                document.getElementById("login").style.display="none";
            }
            else{
                alert('Đăng nhập thất bại');
                alert('Có cái mật khẩu nhập không đúng rồi ai yêu !!!?');
            }
        }
    </script>

</body>
</html>


)=====";
