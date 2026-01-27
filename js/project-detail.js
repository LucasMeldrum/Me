// Project Detail Page Functionality
document.addEventListener('DOMContentLoaded', function() {
  // Get project ID from URL
  const urlParams = new URLSearchParams(window.location.search);
  const projectId = urlParams.get('id') || 'project1';
  
  // Project data
  const projectsData = {
    project1: {
      title: "3D Design: Pyramids & Mathematical Art",
      category: "Art & Design",
      year: "2023",
      description: "Accurate-to-scale 3D reconstruction of Nubian pyramids using SketchUp, featuring vector art and mathematical visualization. This project involved detailed research on architectural proportions and mathematical patterns found in ancient structures.",
      images: [
        "assets/images/pyramids/3DPyramids.png",
        "assets/images/pyramids/3DPyramids.png", // Add more images as needed
        "assets/images/pyramids/3DPyramids.png"
      ],
      tech: ["SketchUp", "3D Modeling", "Vector Art", "Mathematics", "Architecture"],
      duration: "2 months",
      tools: "SketchUp Pro, Adobe Illustrator",
      role: "3D Modeler & Designer",
      github: null,
      demo: null,
      assets: "#",
      challenges: [
        "Achieving accurate scale and proportions based on archaeological data",
        "Creating mathematical visualizations of architectural patterns",
        "Balancing artistic interpretation with historical accuracy"
      ],
      prev: null,
      next: "project2"
    },
    
    project2: {
      title: "Album Cover Design",
      category: "Art & Design",
      year: "2023",
      description: "Complete album artwork including front cover, back design, and inserts created with photography and digital editing. The design process involved conceptualizing the artist's vision and translating it into a cohesive visual identity.",
      images: [
        "assets/images/album/AlbumFront.png",
        "assets/images/album/AlbumBack.png",
        "assets/images/album/Final.png"
      ],
      tech: ["Photoshop", "Photography", "Digital Editing", "Graphic Design"],
      duration: "3 weeks",
      tools: "Adobe Photoshop, DSLR Camera",
      role: "Photographer & Graphic Designer",
      github: null,
      demo: null,
      assets: "#",
      challenges: [
        "Capturing the artist's aesthetic through photography",
        "Creating cohesive design across multiple album components",
        "Balancing typography and imagery for maximum impact"
      ],
      prev: "project1",
      next: "project3"
    },
    
    project3: {
      title: "Creative Coding Jams (p5.js)",
      category: "Mixed Media",
      year: "2023",
      description: "A collection of three interactive art projects created during creative coding jams using p5.js and 3D visualization. Each project explores different aspects of generative art and interactive visualizations.",
      images: [
        "assets/images/art-jam/Art-Jam1.png",
        "assets/images/art-jam/Art-Jam2.png",
        "assets/images/art-jam/Art-Jam3.png"
      ],
      tech: ["p5.js", "3D Art", "Creative Coding", "JavaScript", "Generative Art"],
      duration: "1 month",
      tools: "p5.js Web Editor, Visual Studio Code",
      role: "Creative Coder",
      github: "https://github.com/LucasMeldrum/CART253/tree/main/topics/assignments/art-jam",
      demo: "https://lucasmeldrum.github.io/CART253/topics/assignments/art-jam/",
      assets: "#",
      challenges: [
        "Creating interactive experiences with code as the primary medium",
        "Exploring 3D visualization in web-based environments",
        "Balancing artistic expression with technical constraints"
      ],
      prev: "project2",
      next: "project4"
    },
    
    project4: {
      title: "Photography & Digital Editing",
      category: "Art & Design",
      year: "2023",
      description: "Collection of original photography with advanced digital editing and post-processing techniques. This project showcases both technical photography skills and creative post-production work.",
      images: [
        "assets/images/Photography + Digital Art/Photography + Digital Art-1.png",
        "assets/images/Photography + Digital Art/Photography + Digital Art-2.png",
        "assets/images/Photography + Digital Art/Photography + Digital Art-3.png"
      ],
      tech: ["Photography", "Photoshop", "Digital Art", "Post-Processing"],
      duration: "Ongoing",
      tools: "Adobe Photoshop, Lightroom, DSLR Camera",
      role: "Photographer & Digital Artist",
      github: null,
      demo: null,
      assets: "#",
      challenges: [
        "Mastering lighting and composition in photography",
        "Developing advanced Photoshop editing techniques",
        "Creating cohesive visual narratives across different images"
      ],
      prev: "project3",
      next: "project5"
    },
    
    project5: {
      title: "Nature Conservation Poster",
      category: "Art & Design",
      year: "2023",
      description: "Environmental awareness poster combining artistic design with a powerful conservation message. The design uses visual hierarchy and color psychology to effectively communicate the importance of environmental protection.",
      images: [
        "assets/images/Poster/Poster-1.png",
        "assets/images/Poster/Poster-2.png",
        "assets/images/Poster/Poster-3.png"
      ],
      tech: ["Graphic Design", "Illustrator", "Message Design", "Typography"],
      duration: "2 weeks",
      tools: "Adobe Illustrator, InDesign",
      role: "Graphic Designer",
      github: null,
      demo: null,
      assets: "#",
      challenges: [
        "Communicating complex environmental messages visually",
        "Creating compelling typography and layout",
        "Using color and imagery to evoke emotional response"
      ],
      prev: "project4",
      next: "project6"
    },
    
    project6: {
      title: "C++ Tower Defence Game",
      category: "Development",
      year: "2023",
      description: "Complete tower defence game built from scratch in C++ with custom GUI, algorithms, and game mechanics. Features include enemy pathfinding, tower upgrade systems, and multiple game modes.",
      images: [
        "assets/images/default-game.png", // Fallback image
        "assets/images/default-game.png",
        "assets/images/default-game.png"
      ],
      tech: ["C++", "GUI", "Algorithms", "Game Logic", "Data Structures"],
      duration: "3 months",
      tools: "Visual Studio, SFML Library",
      role: "Game Developer & Programmer",
      github: "https://github.com/LucasMeldrum/TowerDefenceC",
      demo: null,
      assets: "#",
      challenges: [
        "Implementing efficient pathfinding algorithms",
        "Creating responsive GUI with C++",
        "Optimizing game performance and memory usage"
      ],
      prev: "project5",
      next: "project7"
    },
    
    project7: {
      title: "Unity Tower Defence Game",
      category: "Game Development",
      year: "2024",
      description: "Enhanced tower defence game with fun mechanics, wave systems, and dynamic enemy pathfinding built in Unity. Features include particle effects, sound design, and polished user interface.",
      images: [
        "assets/images/UnityTowerDefence/BuildPhase.png",
        "assets/images/UnityTowerDefence/TowerKill.gif",
        "assets/images/UnityTowerDefence/TowerPlace.gif"
      ],
      tech: ["Unity", "C#", "Game Mechanics", "3D Graphics", "UI/UX"],
      duration: "2 months",
      tools: "Unity Engine, Blender, Visual Studio",
      role: "Game Developer & Designer",
      github: "https://github.com/LucasMeldrum/CART315/tree/main/Projects/TowerDefence",
      demo: null,
      assets: "#",
      challenges: [
        "Implementing complex enemy AI and behavior systems",
        "Creating engaging progression and upgrade mechanics",
        "Optimizing 3D graphics for smooth performance"
      ],
      prev: "project6",
      next: "project8"
    },
    
    project8: {
      title: "Unplug: Digital Wellbeing App",
      category: "Development",
      year: "2024",
      description: "Mobile app promoting minimal screen time with gamification, competition against friends, and progress tracking. Features include activity logging, achievement systems, and social connectivity.",
      images: [
        "assets/images/Unplug/StatsPage.png",
        "assets/images/Unplug/Emulation.png",
        "assets/images/Unplug/InteractionsBetweenScreens.png"
      ],
      tech: ["Flutter", "Firebase", "Dart", "API Integration", "Mobile Design"],
      duration: "4 months",
      tools: "Flutter, Firebase, Android Studio",
      role: "Full-Stack Mobile Developer",
      github: "https://github.com/LucasMeldrum/CART470_CapstoneProject/tree/main",
      demo: null,
      assets: "#",
      challenges: [
        "Implementing real-time data synchronization with Firebase",
        "Creating engaging gamification elements",
        "Designing intuitive mobile user interface"
      ],
      prev: "project7",
      next: "project9"
    },
    
    project9: {
      title: "Variation Jam: Yars Revenge",
      category: "Game Development",
      year: "2023",
      description: "Creative modification of Yars Revenge using p5.js, featuring new gameplay mechanics and visual styles. This project reimagines a classic arcade game with modern creative coding techniques.",
      images: [
        "assets/images/variation-jam/Var1.png",
        "assets/images/variation-jam/Var2.png",
        "assets/images/variation-jam/Var3.png"
      ],
      tech: ["p5.js", "Game Design", "Retro Games", "Creative Coding"],
      duration: "2 weeks",
      tools: "p5.js Web Editor, JavaScript",
      role: "Game Developer & Creative Coder",
      github: "https://github.com/LucasMeldrum/CART253/tree/main/topics/assignments/variation-jam",
      demo: "https://lucasmeldrum.github.io/CART253/topics/assignments/variation-jam",
      assets: "#",
      challenges: [
        "Modernizing classic game mechanics",
        "Creating engaging variations within technical constraints",
        "Balancing nostalgia with innovation"
      ],
      prev: "project8",
      next: "project10"
    },
    
    project10: {
      title: "BandTogether: Ubisoft Competition Game",
      category: "Game Development",
      year: "2024",
      description: "Unity game developed for Ubisoft competition. Large team project with complex mechanics over an extended development period. Features multiplayer elements and advanced game systems.",
      images: [
        "assets/images/bandtogether/3.gif",
        "assets/images/bandtogether/Screenshot 2026-01-15 at 9.35.10 PM.png",
        "assets/images/bandtogether/Screenshot 2026-01-15 at 9.35.27 PM.png"
      ],
      tech: ["Unity", "Team Leadership", "Game Design", "Competition", "C#"],
      duration: "6 months",
      tools: "Unity Engine, Git, Trello, Blender",
      role: "Team Lead & Game Developer",
      github: null,
      demo: null,
      assets: "#",
      challenges: [
        "Coordinating large development team with diverse skill sets",
        "Implementing complex game mechanics within competition timeline",
        "Maintaining code quality and documentation throughout development"
      ],
      prev: "project9",
      next: null
    }
  };

  // Load project data
  const project = projectsData[projectId];
  
  if (!project) {
    // Redirect to main page if project not found
    window.location.href = "index.html#projects";
    return;
  }

  // Update page content
  document.getElementById('projectTitle').textContent = project.title;
  document.getElementById('projectCategory').textContent = project.category;
  document.getElementById('projectYear').textContent = project.year;
  document.getElementById('projectDescription').textContent = project.description;
  document.getElementById('projectDuration').textContent = project.duration;
  document.getElementById('projectTools').textContent = project.tools;
  document.getElementById('projectRole').textContent = project.role;
  
  // Update page title
  document.title = `${project.title} | Lucas Meldrum`;

  // Update tech tags
  const techContainer = document.getElementById('projectTech');
  techContainer.innerHTML = '';
  project.tech.forEach(tech => {
    const tag = document.createElement('span');
    tag.className = 'tech-tag';
    tag.textContent = tech;
    techContainer.appendChild(tag);
  });

  // Update challenges list
  const challengesList = document.getElementById('challengesList');
  challengesList.innerHTML = '';
  project.challenges.forEach(challenge => {
    const li = document.createElement('li');
    li.textContent = challenge;
    challengesList.appendChild(li);
  });

  // Update links
  const githubLink = document.getElementById('githubLink');
  const demoLink = document.getElementById('demoLink');
  const downloadLink = document.getElementById('downloadLink');
  
  if (project.github) {
    githubLink.href = project.github;
    githubLink.style.display = 'flex';
  } else {
    githubLink.style.display = 'none';
  }
  
  if (project.demo) {
    demoLink.href = project.demo;
    demoLink.style.display = 'flex';
  } else {
    demoLink.style.display = 'none';
  }
  
  if (project.assets) {
    downloadLink.href = project.assets;
  }

  // Initialize gallery
  let currentImageIndex = 0;
  const mainImage = document.getElementById('mainImage');
  const thumbnailGallery = document.getElementById('thumbnailGallery');
  const currentImageSpan = document.getElementById('currentImage');
  const totalImagesSpan = document.getElementById('totalImages');
  const prevBtn = document.querySelector('.prev-btn');
  const nextBtn = document.querySelector('.next-btn');

  // Set total images
  totalImagesSpan.textContent = project.images.length;

  // Create thumbnails
  thumbnailGallery.innerHTML = '';
  project.images.forEach((image, index) => {
    const thumbnail = document.createElement('div');
    thumbnail.className = 'thumbnail-item';
    if (index === 0) thumbnail.classList.add('active');
    
    const img = document.createElement('img');
    img.src = image;
    img.alt = `${project.title} - Image ${index + 1}`;
    img.loading = 'lazy';
    
    thumbnail.appendChild(img);
    thumbnail.addEventListener('click', () => showImage(index));
    thumbnailGallery.appendChild(thumbnail);
  });

  // Set initial main image
  function showImage(index) {
    currentImageIndex = index;
    mainImage.src = project.images[index];
    mainImage.alt = `${project.title} - Image ${index + 1}`;
    currentImageSpan.textContent = index + 1;
    
    // Update active thumbnail
    document.querySelectorAll('.thumbnail-item').forEach((item, i) => {
      item.classList.toggle('active', i === index);
    });
  }

  // Navigation functions
  function nextImage() {
    currentImageIndex = (currentImageIndex + 1) % project.images.length;
    showImage(currentImageIndex);
  }

  function prevImage() {
    currentImageIndex = (currentImageIndex - 1 + project.images.length) % project.images.length;
    showImage(currentImageIndex);
  }

  // Event listeners
  prevBtn.addEventListener('click', prevImage);
  nextBtn.addEventListener('click', nextImage);

  // Keyboard navigation
  document.addEventListener('keydown', (e) => {
    if (e.key === 'ArrowLeft') prevImage();
    if (e.key === 'ArrowRight') nextImage();
  });

  // Initialize with first image
  showImage(0);

  // Update project navigation
  const prevProjectBtn = document.getElementById('prevProject');
  const nextProjectBtn = document.getElementById('nextProject');
  
  if (project.prev && projectsData[project.prev]) {
    prevProjectBtn.href = `project-detail.html?id=${project.prev}`;
    document.getElementById('prevProjectTitle').textContent = projectsData[project.prev].title;
    prevProjectBtn.style.display = 'flex';
  } else {
    prevProjectBtn.style.display = 'none';
  }
  
  if (project.next && projectsData[project.next]) {
    nextProjectBtn.href = `project-detail.html?id=${project.next}`;
    document.getElementById('nextProjectTitle').textContent = projectsData[project.next].title;
    nextProjectBtn.style.display = 'flex';
  } else {
    nextProjectBtn.style.display = 'none';
  }

  // Set current year in footer
  document.getElementById('currentYear').textContent = new Date().getFullYear();
});