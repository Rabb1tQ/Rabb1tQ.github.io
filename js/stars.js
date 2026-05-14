(function () {
  var canvas = document.getElementById('stars-canvas');
  if (!canvas) return;

  function isDark() {
    var s = document.documentElement.getAttribute('data-md-color-scheme');
    if (s === 'slate') return true;
    if (s === 'default') return false;
    return window.matchMedia('(prefers-color-scheme: dark)').matches;
  }

  var ctx = canvas.getContext('2d');
  var particles = [];
  var w, h;
  var mouse = { x: -9999, y: -9999 };
  var CONNECT_DIST = 140;
  var MOUSE_DIST = 200;

  function resize() {
    w = canvas.width = window.innerWidth;
    h = canvas.height = window.innerHeight;
  }

  function init() {
    particles = [];
    var count = Math.min(Math.floor((w * h) / 18000), 120);
    for (var i = 0; i < count; i++) {
      particles.push({
        x: Math.random() * w,
        y: Math.random() * h,
        vx: (Math.random() - 0.5) * 0.4,
        vy: (Math.random() - 0.5) * 0.4,
        r: Math.random() * 1.8 + 0.5,
        a: Math.random() * 0.5 + 0.2,
      });
    }
  }

  function draw() {
    if (!isDark()) {
      canvas.style.display = 'none';
      document.getElementById('starry-bg').style.display = 'none';
      requestAnimationFrame(draw);
      return;
    }
    canvas.style.display = 'block';
    document.getElementById('starry-bg').style.display = 'block';

    ctx.clearRect(0, 0, w, h);

    for (var i = 0; i < particles.length; i++) {
      var p = particles[i];
      p.x += p.vx;
      p.y += p.vy;
      if (p.x < 0) p.x = w;
      if (p.x > w) p.x = 0;
      if (p.y < 0) p.y = h;
      if (p.y > h) p.y = 0;

      ctx.beginPath();
      ctx.arc(p.x, p.y, p.r, 0, Math.PI * 2);
      ctx.fillStyle = 'rgba(140,180,220,' + p.a + ')';
      ctx.fill();
    }

    for (var i = 0; i < particles.length; i++) {
      for (var j = i + 1; j < particles.length; j++) {
        var dx = particles[i].x - particles[j].x;
        var dy = particles[i].y - particles[j].y;
        var dist = Math.sqrt(dx * dx + dy * dy);
        if (dist < CONNECT_DIST) {
          var alpha = (1 - dist / CONNECT_DIST) * 0.15;
          ctx.beginPath();
          ctx.moveTo(particles[i].x, particles[i].y);
          ctx.lineTo(particles[j].x, particles[j].y);
          ctx.strokeStyle = 'rgba(109,213,250,' + alpha + ')';
          ctx.lineWidth = 0.5;
          ctx.stroke();
        }
      }

      var mdx = particles[i].x - mouse.x;
      var mdy = particles[i].y - mouse.y;
      var mdist = Math.sqrt(mdx * mdx + mdy * mdy);
      if (mdist < MOUSE_DIST) {
        var malpha = (1 - mdist / MOUSE_DIST) * 0.3;
        ctx.beginPath();
        ctx.moveTo(particles[i].x, particles[i].y);
        ctx.lineTo(mouse.x, mouse.y);
        ctx.strokeStyle = 'rgba(200,160,255,' + malpha + ')';
        ctx.lineWidth = 0.6;
        ctx.stroke();
      }
    }

    requestAnimationFrame(draw);
  }

  resize();
  init();
  draw();

  window.addEventListener('resize', function () {
    resize();
    init();
  });

  window.addEventListener('mousemove', function (e) {
    mouse.x = e.clientX;
    mouse.y = e.clientY;
  });

  window.addEventListener('mouseleave', function () {
    mouse.x = -9999;
    mouse.y = -9999;
  });
})();
