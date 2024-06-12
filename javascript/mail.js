const firebaseConfig = {
    apiKey: "AIzaSyCuFG4FT2fUKXZcqdkUdev4rx5nHEkQt0w",
    authDomain: "esp8266-282ed.firebaseapp.com",
    databaseURL: "https://esp8266-282ed-default-rtdb.firebaseio.com",
    projectId: "esp8266-282ed",
    storageBucket: "esp8266-282ed.appspot.com",
    messagingSenderId: "980208546762",
    appId: "1:980208546762:web:81b04c03fcb9b36ac95533",
    measurementId: "G-KHQW2FK2P2"
  };
  
  // initialize firebase
  firebase.initializeApp(firebaseConfig);
  
  // reference your database
  var intesDB = firebase.database().ref("itens");
  
  document.getElementById("itens").addEventListener("submit", submitForm);
  
  function submitForm(e) {
    e.preventDefault();
  
    var name = getElementVal("name");
    var emailid = getElementVal("emailid");
    var msgContent = getElementVal("msgContent");
  
    saveMessages(name, emailid, msgContent);
  
    //   enable alert
    document.querySelector(".alert").style.display = "block";
  
    //   remove the alert
    setTimeout(() => {
      document.querySelector(".alert").style.display = "none";
    }, 3000);
  
    //   reset the form
    document.getElementById("contactForm").reset();
  }
  
  const saveMessages = (name, emailid, msgContent) => {
    var newContactForm = contactFormDB.push();
  
    newContactForm.set({
      name: name,
      emailid: emailid,
      msgContent: msgContent,
    });
  };
  
  const getElementVal = (id) => {
    return document.getElementById(id).value;
  };
