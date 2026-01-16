// DOM Elements
const progressBar = document.getElementById('progressBar');
const themeToggle = document.getElementById('themeToggle');
const menuToggle = document.getElementById('menuToggle');
const navLinks = document.querySelector('.nav-links');
const filterButtons = document.querySelectorAll('.filter-btn');
const projectCards = document.querySelectorAll('.project-card');
const contactForm = document.getElementById('contactForm');
const currentYear = document.getElementById('currentYear');

// Theme Management
function initTheme() {
  const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
  const savedTheme = localStorage.getItem('theme') || (prefersDark ? 'dark' : 'light');
  document.documentElement.setAttribute('data-theme', savedTheme);
  updateThemeIcon(savedTheme);
}

function toggleTheme() {
  const currentTheme = document.documentElement.getAttribute('data-theme');
  const newTheme = currentTheme === 'dark' ? 'light' : 'dark';
  
  document.documentElement.setAttribute('data-theme', newTheme);
  localStorage.setItem('theme', newTheme);
  updateThemeIcon(newTheme);
  
  // Add transition effect
  document.body.style.transition = 'background-color 0.3s ease, color 0.3s ease';
  setTimeout(() => {
    document.body.style.transition = '';
  }, 300);
}

function updateThemeIcon(theme) {
  const icon = themeToggle.querySelector('i');
  icon.className = theme === 'dark' ? 'ti ti-sun' : 'ti ti-moon';
}

// Progress Bar
function updateProgressBar() {
  const scrollTop = window.pageYOffset;
  const docHeight = document.documentElement.scrollHeight - window.innerHeight;
  const scrollPercent = (scrollTop / docHeight) * 100;
  progressBar.style.width = `${scrollPercent}%`;
}

// Mobile Menu
function toggleMenu() {
  navLinks.classList.toggle('active');
  const isOpen = navLinks.classList.contains('active');
  menuToggle.innerHTML = isOpen ? '<i class="ti ti-x"></i>' : '<i class="ti ti-menu-2"></i>';
  document.body.style.overflow = isOpen ? 'hidden' : '';
}

// Project Filtering
function filterProjects(filter) {
  // Update active button
  filterButtons.forEach(btn => {
    btn.classList.toggle('active', btn.dataset.filter === filter);
  });

  // Filter projects
  let visibleCount = 0;
  projectCards.forEach((card, index) => {
    const category = card.dataset.category;
    const shouldShow = filter === 'all' || category === filter;
    
    if (shouldShow) {
      visibleCount++;
      card.style.display = 'block';
      
      // Stagger animation
      setTimeout(() => {
        card.style.opacity = '1';
        card.style.transform = 'translateY(0)';
      }, index * 50);
    } else {
      card.style.opacity = '0';
      card.style.transform = 'translateY(20px)';
      setTimeout(() => {
        card.style.display = 'none';
      }, 300);
    }
  });
  
  // Show message if no projects
  const grid = document.querySelector('.projects-grid');
  let message = grid.querySelector('.no-projects');
  
  if (visibleCount === 0) {
    if (!message) {
      message = document.createElement('div');
      message.className = 'no-projects';
      message.innerHTML = `
        <h3>No projects found in this category</h3>
        <p>Try selecting another filter or view all projects.</p>
      `;
      grid.appendChild(message);
    }
  } else if (message) {
    message.remove();
  }
}

// Image Carousel
function initImageCarousels() {
  const carousels = document.querySelectorAll('.image-carousel');
  
  carousels.forEach(carousel => {
    const images = carousel.querySelectorAll('img');
    if (images.length <= 1) return;
    
    let currentIndex = 0;
    const totalImages = images.length;
    
    // Set initial position
    carousel.style.width = `${totalImages * 100}%`;
    images.forEach(img => {
      img.style.width = `${100 / totalImages}%`;
    });
    
    // Auto rotate every 4 seconds
    const interval = setInterval(() => {
      currentIndex = (currentIndex + 1) % totalImages;
      carousel.style.transform = `translateX(-${currentIndex * (100 / totalImages)}%)`;
    }, 4000);
    
    // Pause on hover
    carousel.parentElement.addEventListener('mouseenter', () => {
      clearInterval(interval);
    });
    
    carousel.parentElement.addEventListener('mouseleave', () => {
      setInterval(() => {
        currentIndex = (currentIndex + 1) % totalImages;
        carousel.style.transform = `translateX(-${currentIndex * (100 / totalImages)}%)`;
      }, 4000);
    });
  });
}

// Form Submission
async function handleSubmit(event) {
  event.preventDefault();
  
  const form = event.target;
  const formData = new FormData(form);
  const submitBtn = form.querySelector('button[type="submit"]');
  const originalText = submitBtn.innerHTML;
  
  // Show loading state
  submitBtn.innerHTML = '<i class="ti ti-loader spin"></i> Sending...';
  submitBtn.disabled = true;
  
  try {
    // In a real application, you would send this data to a server
    const data = Object.fromEntries(formData);
    
    // Simulate API call
    await new Promise(resolve => setTimeout(resolve, 1500));
    
    // Show success message
    showNotification('Message sent successfully! I\'ll get back to you soon.', 'success');
    form.reset();
    
  } catch (error) {
    showNotification('Failed to send message. Please try again.', 'error');
  } finally {
    // Reset button state
    submitBtn.innerHTML = originalText;
    submitBtn.disabled = false;
  }
}

// Notification System
function showNotification(message, type = 'info') {
  const notification = document.createElement('div');
  notification.className = `notification notification-${type}`;
  notification.innerHTML = `
    <div class="notification-content">
      <i class="ti ti-${type === 'success' ? 'circle-check' : 'alert-circle'}"></i>
      <span>${message}</span>
    </div>
    <button class="notification-close"><i class="ti ti-x"></i></button>
  `;
  
  document.body.appendChild(notification);
  
  // Add styles if not already added
  if (!document.querySelector('#notification-styles')) {
    const style = document.createElement('style');
    style.id = 'notification-styles';
    style.textContent = `
      .notification {
        position: fixed;
        top: 20px;
        right: 20px;
        background: var(--bg-card);
        border: 1px solid var(--border-color);
        border-left: 4px solid var(--accent-primary);
        border-radius: var(--radius-md);
        padding: 1rem 1.5rem;
        display: flex;
        align-items: center;
        justify-content: space-between;
        gap: 1rem;
        max-width: 400px;
        box-shadow: var(--shadow-lg);
        z-index: 9999;
        transform: translateX(120%);
        transition: transform 0.3s ease;
      }
      .notification-success {
        border-left-color: #10b981;
      }
      .notification-error {
        border-left-color: #ef4444;
      }
      .notification-content {
        display: flex;
        align-items: center;
        gap: 0.75rem;
      }
      .notification i {
        font-size: 1.25rem;
      }
      .notification-success i {
        color: #10b981;
      }
      .notification-error i {
        color: #ef4444;
      }
      .notification-close {
        background: none;
        border: none;
        color: var(--text-muted);
        cursor: pointer;
        padding: 0.25rem;
        border-radius: var(--radius-sm);
      }
      .notification-close:hover {
        background: var(--bg-secondary);
      }
    `;
    document.head.appendChild(style);
  }
  
  // Show notification
  setTimeout(() => {
    notification.style.transform = 'translateX(0)';
  }, 10);
  
  // Close button
  notification.querySelector('.notification-close').addEventListener('click', () => {
    notification.style.transform = 'translateX(120%)';
    setTimeout(() => notification.remove(), 300);
  });
  z
  // Auto remove after 5 seconds
  setTimeout(() => {
    if (notification.parentNode) {
      notification.style.transform = 'translateX(120%)';
      setTimeout(() => notification.remove(), 300);
    }
  }, 5000);
}

// Smooth Scrolling
function smoothScroll(target) {
  const element = document.querySelector(target);
  if (element) {
    const offset = 80; // Navigation height
    const elementPosition = element.offsetTop - offset;
    
    window.scrollTo({
      top: elementPosition,
      behavior: 'smooth'
    });
  }
}

// Intersection Observer for animations
function initIntersectionObserver() {
  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.classList.add('active');
        
        // Animate skill bars
        if (entry.target.classList.contains('skill-bar')) {
          entry.target.style.width = entry.target.getAttribute('data-width') || '100%';
        }
      }
    });
  }, { 
    threshold: 0.1,
    rootMargin: '0px 0px -50px 0px'
  });

  // Observe elements with reveal class
  document.querySelectorAll('.reveal').forEach(el => observer.observe(el));
  
  // Observe skill bars
  document.querySelectorAll('.skill-bar').forEach(el => {
    const width = el.style.width;
    el.setAttribute('data-width', width);
    el.style.width = '0';
    observer.observe(el);
  });
}

// Initialize Particles
function initParticles() {
  const hero = document.querySelector('.hero');
  if (!hero) return;
  
  const particleCount = 20;
  
  for (let i = 0; i < particleCount; i++) {
    const particle = document.createElement('div');
    particle.className = 'particle';
    
    // Random properties
    const size = Math.random() * 4 + 1;
    const x = Math.random() * 100;
    const y = Math.random() * 100;
    const duration = Math.random() * 10 + 10;
    const delay = Math.random() * 5;
    
    particle.style.width = `${size}px`;
    particle.style.height = `${size}px`;
    particle.style.left = `${x}%`;
    particle.style.top = `${y}%`;
    particle.style.opacity = Math.random() * 0.3 + 0.1;
    particle.style.background = `linear-gradient(135deg, 
      rgba(${Math.random() > 0.5 ? '139, 92, 246' : '250, 204, 21'}, ${Math.random() * 0.5 + 0.3}) 0%, 
      rgba(${Math.random() > 0.5 ? '59, 130, 246' : '34, 211, 153'}, ${Math.random() * 0.5 + 0.3}) 100%)`;
    particle.style.animation = `float-particle ${duration}s linear ${delay}s infinite`;
    
    hero.appendChild(particle);
  }
}

// Project Counter Animation
function animateProjectCounter() {
  const counter = document.querySelector('.stat-number');
  if (!counter || !isElementInViewport(counter)) return;
  
  const target = parseInt(counter.textContent);
  let current = 0;
  const increment = target / 50;
  const duration = 1500;
  const interval = duration / 50;
  
  const timer = setInterval(() => {
    current += increment;
    if (current >= target) {
      current = target;
      clearInterval(timer);
    }
    counter.textContent = Math.floor(current);
  }, interval);
}

// Check if element is in viewport
function isElementInViewport(el) {
  const rect = el.getBoundingClientRect();
  return (
    rect.top >= 0 &&
    rect.left >= 0 &&
    rect.bottom <= (window.innerHeight || document.documentElement.clientHeight) &&
    rect.right <= (window.innerWidth || document.documentElement.clientWidth)
  );
}

// Initialize everything
function init() {
  // Set current year
  currentYear.textContent = new Date().getFullYear();
  
  // Initialize theme
  initTheme();
  
  // Initialize animations
  initIntersectionObserver();
  initImageCarousels();
  initParticles();
  
  // Set initial animations
  document.querySelectorAll('.stagger-children > *').forEach((el, index) => {
    el.style.animationDelay = `${index * 0.1}s`;
  });
  
  // Event Listeners
  window.addEventListener('scroll', () => {
    updateProgressBar();
    animateProjectCounter();
  });
  
  themeToggle.addEventListener('click', toggleTheme);
  menuToggle.addEventListener('click', toggleMenu);
  
  // Filter buttons
  filterButtons.forEach(btn => {
    btn.addEventListener('click', () => {
      filterProjects(btn.dataset.filter);
    });
  });
  
  // Smooth scroll for navigation links
  document.querySelectorAll('a[href^="#"]').forEach(link => {
    link.addEventListener('click', (e) => {
      const href = link.getAttribute('href');
      if (href === '#') return;
      
      e.preventDefault();
      smoothScroll(href);
      
      if (window.innerWidth <= 768) {
        toggleMenu();
      }
    });
  });
  
  // Form submission
  if (contactForm) {
    contactForm.addEventListener('submit', handleSubmit);
  }
  
  // Close menu when clicking outside
  document.addEventListener('click', (e) => {
    if (!e.target.closest('.nav-links') && !e.target.closest('.menu-toggle')) {
      navLinks.classList.remove('active');
      menuToggle.innerHTML = '<i class="ti ti-menu-2"></i>';
      document.body.style.overflow = '';
    }
  });
  
  // Keyboard navigation
  document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') {
      navLinks.classList.remove('active');
      menuToggle.innerHTML = '<i class="ti ti-menu-2"></i>';
      document.body.style.overflow = '';
    }
  });
  
  // Initialize project counter animation
  setTimeout(animateProjectCounter, 1000);
  
  // Add loading class to body for initial animations
  document.body.classList.add('page-load');
}

// Initialize when DOM is loaded
document.addEventListener('DOMContentLoaded', init);

// Add CSS for spinner
const spinnerStyle = document.createElement('style');
spinnerStyle.textContent = `
  .spin {
    animation: spin 1s linear infinite;
  }
  
  @keyframes spin {
    from { transform: rotate(0deg); }
    to { transform: rotate(360deg); }
  }
`;
document.head.appendChild(spinnerStyle);