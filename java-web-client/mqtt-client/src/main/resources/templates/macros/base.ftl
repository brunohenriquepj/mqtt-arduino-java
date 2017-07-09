<#include "navbar.ftl">
<#include "footer.ftl">
<#macro page_head>
    <title>ArduinoMQTT</title>
</#macro>

<#macro page_body>
    <h1>Basic Page</h1>
    <p>This is the body of the page!</p>
</#macro>


<#macro display_page>

<!DOCTYPE html>
<html lang="en">
<head>
    <@page_head/>
    <link type="text/css" rel="stylesheet" href="/css/materialize/css/materialize.min.css"  media="screen,projection"/>
    <link rel="stylesheet" href="/icons/font-awesome-4.7.0/css/font-awesome.min.css">
    <link rel="stylesheet" href="/css/main.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <meta name="theme-color" content="#0097a7" />
    <script type="text/javascript" src="/js/jquery-2.1.1.min.js"></script>
</head>
<body>
    <@display_navbar/>
    <main>
        <div class="container">
            <div class="row">
                <div class="col l12 s12">
                    <@page_body/>
                </div>
            </div>
        </div>
    </main>
    <@display_footer/>

    <script type="text/javascript" src="/css/materialize/js/materialize.min.js"></script>
    <script src="/webjars/sockjs-client/sockjs.min.js"></script>
    <script src="/webjars/stomp-websocket/stomp.min.js"></script>
</body>
</html>

</#macro>