<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=us-ascii" />
<title>doc/html/boost_asio/example/http/server3/win_main.cpp - 1.46.1</title>  <link rel="icon" href="/favicon.ico" type="image/ico" />
  <link rel="stylesheet" type="text/css" href="/style-v2/section-doc.css" />
  <!--[if IE 7]> <style type="text/css"> body { behavior: url(/style-v2/csshover3.htc); } </style> <![endif]-->

</head>

<body>
  <div id="heading">
    <div class="heading-inner">
  <div class="heading-placard"></div>

  <h1 class="heading-title">
  <a href="/">
  <img src="/gfx/space.png" alt= "Boost C++ Libraries" class="heading-logo" />
  <span class="heading-boost">Boost</span>
  <span class="heading-cpplibraries">C++ Libraries</span>
  </a></h1>

  <p class="heading-quote">
  <q>...one of the most highly
  regarded and expertly designed C++ library projects in the
  world.</q> <span class="heading-attribution">&mdash; <a href=
  "http://www.gotw.ca/" class="external">Herb Sutter</a> and <a href=
  "http://en.wikipedia.org/wiki/Andrei_Alexandrescu" class="external">Andrei
  Alexandrescu</a>, <a href=
  "http://safari.awprofessional.com/?XmlId=0321113586" class="external">C++
  Coding Standards</a></span></p>
</div>
<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-33761719-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>
  </div>

  <div id="body">
    <div id="body-inner">
      <div id="content">
        <div class="section" id="docs">
          <div class="section-0">
            <div class="section-body">
              <h3>doc/html/boost_asio/example/http/server3/win_main.cpp</h3>
<pre>
//
// win_main.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at <a href="http://www.boost.org/LICENSE_1_0.txt">http://www.boost.org/LICENSE_1_0.txt</a>)
//

#include &lt;iostream&gt;
#include &lt;string&gt;
#include &lt;<a href="../../../../../../boost/asio.hpp">boost/asio.hpp</a>&gt;
#include &lt;<a href="../../../../../../boost/bind.hpp">boost/bind.hpp</a>&gt;
#include &lt;<a href="../../../../../../boost/function.hpp">boost/function.hpp</a>&gt;
#include &lt;<a href="../../../../../../boost/lexical_cast.hpp">boost/lexical_cast.hpp</a>&gt;
#include &quot;server.hpp&quot;

#if defined(_WIN32)

boost::function0&lt;void&gt; console_ctrl_function;

BOOL WINAPI console_ctrl_handler(DWORD ctrl_type)
{
  switch (ctrl_type)
  {
  case CTRL_C_EVENT:
  case CTRL_BREAK_EVENT:
  case CTRL_CLOSE_EVENT:
  case CTRL_SHUTDOWN_EVENT:
    console_ctrl_function();
    return TRUE;
  default:
    return FALSE;
  }
}

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 5)
    {
      std::cerr &lt;&lt; &quot;Usage: http_server &lt;address&gt; &lt;port&gt; &lt;threads&gt; &lt;doc_root&gt;\n&quot;;
      std::cerr &lt;&lt; &quot;  For IPv4, try:\n&quot;;
      std::cerr &lt;&lt; &quot;    http_server 0.0.0.0 80 1 .\n&quot;;
      std::cerr &lt;&lt; &quot;  For IPv6, try:\n&quot;;
      std::cerr &lt;&lt; &quot;    http_server 0::0 80 1 .\n&quot;;
      return 1;
    }

    // Initialise server.
    std::size_t num_threads = boost::lexical_cast&lt;std::size_t&gt;(argv[3]);
    http::server3::server s(argv[1], argv[2], argv[4], num_threads);

    // Set console control handler to allow server to be stopped.
    console_ctrl_function = boost::bind(&amp;http::server3::server::stop, &amp;s);
    SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception&amp; e)
  {
    std::cerr &lt;&lt; &quot;exception: &quot; &lt;&lt; e.what() &lt;&lt; &quot;\n&quot;;
  }

  return 0;
}

#endif // defined(_WIN32)
</pre>
            </div>
          </div>
        </div>
      </div>

      <div class="clear"></div>
    </div>
  </div>

  <div id="footer">
    <div id="footer-left">
      <div id="revised">
        <p>Revised $Date$</p>
      </div>

      <div id="copyright">
        <p>Copyright Beman Dawes, David Abrahams, 1998-2005.</p>

        <p>Copyright Rene Rivera 2004-2008.</p>
      </div>  <div id="license">
    <p>Distributed under the <a href="/LICENSE_1_0.txt" class=
    "internal">Boost Software License, Version 1.0</a>.</p>
  </div>
    </div>

    <div id="footer-right">
        <div id="banners">
    <p id="banner-xhtml"><a href="http://validator.w3.org/check?uri=referer"
    class="external">XHTML 1.0</a></p>

    <p id="banner-css"><a href=
    "http://jigsaw.w3.org/css-validator/check/referer" class=
    "external">CSS</a></p>

    <p id="banner-osi"><a href=
    "http://www.opensource.org/docs/definition.php" class="external">OSI
    Certified</a></p>
  </div>
    </div>

    <div class="clear"></div>
  </div>
</body>
</html>